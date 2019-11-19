#include "inputoutput.h"
#include "metropolis.h"


void AskForInput(int L, int MonteCarloCycles, int Approach, string SpinConfig){
    ofstream ofile;
    double Temperature; 

    // Defining filename for different methods
    string Single_Temp = "Singel_Temp.txt";
    string Temp = "Temperature.txt";
    string Monte = "MonteCarloCycles.txt";
    string Spins = "SpinConfig.txt";
    string Accepted = "Accepted_Flips.txt";
    string Reached_Equilibrium = "Data_After_Equilibrium.txt";
    string MonteExpectiationValues ="MonteExpect.txt";

    if (Approach == 1){
        cout << "Insert Temperature:" << endl;
        cin >> Temperature;
        ofile.open(Single_Temp);
        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
        GenerateTableBottom(ofile);
    }
    else if (Approach == 2){
        double initial_temp, final_temp, temp_step;
        cout << "Insert choice of initial temp:" << endl;
        cin >> initial_temp;
        cout << "Insert final temperture:" << endl;
        cin >> final_temp;
        cout << "Insert temp step" << endl;
        cin >> temp_step;

        ofile.open(Temp);

        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);

        // Defining new variables to for loop over an int (Beacuse of Pragma)
        int Int_Temp = initial_temp*10000000;
        int Final_Temp = final_temp*10000000;
        int Temp_Step = temp_step*10000000;

        // Parallelization is done in this part if you don't want to run Pragma Parallelization
        // Comment out the parts here that have (Parallell) as comment in them

        cout << omp_get_num_procs() << endl;     // (Parallell)

        omp_set_num_threads(4);                // (Parallell)
        double StartTime = omp_get_wtime();    // (Parallell)
        #pragma omp parallel for               // (Parallell)
        for (int TempInterval = Int_Temp; TempInterval < Final_Temp; TempInterval+=Temp_Step){
            //Pragma wouldn't for loop for a double so converting to int and then to double again
            Temperature = (double) TempInterval/10000000;
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
            cout << "Current Temperature: " << Temperature << endl;
        }
        GenerateTableBottom(ofile);
        double StopTime = omp_get_wtime();           // (Parallell)

        double TotalTime = StopTime-StartTime;       // (Parallell)
        cout << "Total Time: " << TotalTime << endl; // (Parallell)

    }
    else if (Approach == 3){
        int Equilibrium;
        cout << "Equilibrum Monte Carlo cylces:" << endl;
        cin >> Equilibrium;
        cout << "Insert Temperature:" << endl;
        cin >> Temperature;
        ofile.open(Reached_Equilibrium);

        GenerateTableTopMonteCarlo(ofile, L, Temperature, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, Equilibrium);
        GenerateTableBottom(ofile);
    }
    else if(Approach == 4){
        int initial_mont, final_mont, mont_step;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        cout << "Insert initial Monte Carlo cycles" << endl;
        cin >> initial_mont;
        cout << "Insert final Monte Carlo cycles" << endl;
        cin >> final_mont;
        cout << "Insert Monte Carlo cycles-step" << endl;
        cin >> mont_step;

        ofile.open(Spins);
        for (int MonteCarloCycles = initial_mont; MonteCarloCycles <= final_mont; MonteCarloCycles+=mont_step){
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
        }
    }

    else if (Approach == 5){
        cout << "Insert Temperature: " << endl;
        cin >> Temperature;
        ofile.open(Accepted);

        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
        GenerateTableBottom(ofile);
    }
    else if (Approach == 6){
        int Equilibrium;
        cout << "Equilibrum Monte Carlo Cycles:" << endl;
        cin >> Equilibrium;
        cout << "Insert Temperature: " << endl;
        cin >> Temperature;

        ofile.open(MonteExpectiationValues);
        GenerateTableTopMonteCarlo(ofile, L, Temperature, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, Equilibrium);
        GenerateTableBottom(ofile);
    }
    ofile.close();
}


void GenerateTableTop(ofstream& ofile, int L, int MonteCarloCycles, string SpinConfig){
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Spin Matrix: " << L << "x" << L << endl;
    ofile << "Number of Monte Carlo Cycles: " << MonteCarloCycles << endl;
    ofile << "Spin Configuration: " << SpinConfig << endl;
    ofile << "All values are given per spin!\n";
    ofile << "╔═══════════════╤══════════════╤═══════════════╤═══════════════╤════════════════╗\n";
    ofile << "║  Temperature  │    Energy    │ Heat Capacity │ Magnetization │ Susceptibility ║" << endl;
    ofile << "╟───────────────┼──────────────┼───────────────┼───────────────┼────────────────╢\n";

}

void GenerateTableTopMonteCarlo(ofstream& ofile, int L, double Temperature, string SpinConfig){
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Spin Matrix: " << L << "x" << L << endl;
    ofile << "Temperature choice: " << Temperature << endl;
    ofile << "Spin Configuration: " << SpinConfig << endl;
    ofile << "All values are given per spin!\n";
    ofile << "╔═══════════════╤══════════════╤═══════════════╤═══════════════╤════════════════╗\n";
    ofile << "║  Monte Carlo  │    Energy    │ Heat Capacity │ Magnetization │ Susceptibility ║" << endl;
    ofile << "╟───────────────┼──────────────┼───────────────┼───────────────┼────────────────╢\n";

}


void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues){
    double Normalization = 1/((double) (MonteCarloCycles)); 
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization; // Not interested in this one
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // All expectation values are given per spin
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << Temperature  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Eaverage/L/L << "  ";
    ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl; // Not interested in this one either
}

void WriteToFileMCvsExpect(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues){
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization;  // Not interested in this one
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // All expectation values are given per spin
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << MonteCarloCycles  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Eaverage/L/L << "  ";
    ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;  // Not interested in this one either
}


void WriteToFileOutputMonteCarlo(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, double Energy){
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << MonteCarloCycles  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Energy/L/L << endl;
}

void WriteToFileOutputMonteSpins(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues, mat SpinMatrix){
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << SpinMatrix  <<endl;
    cout << MonteCarloCycles << endl;
}

void WriteAccepted(ofstream& ofile, int MonteCarloCycles, double Accepted_Flips, int L){
    ofile << setprecision(7) << MonteCarloCycles << "   ";
    ofile << setprecision(7) << Accepted_Flips/MonteCarloCycles << endl; 
}

void GenerateTableBottom(ofstream& ofile){
    ofile << "╚═══════════════╧══════════════╧═══════════════╧═══════════════╧════════════════╝\n";
}