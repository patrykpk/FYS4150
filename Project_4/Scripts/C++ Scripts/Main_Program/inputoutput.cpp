#include "inputoutput.h"
#include "metropolis.h"


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
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << Temperature  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Eaverage/L/L << "  ";
    ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;
}

void WriteToFileMCvsExpect(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues){
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << MonteCarloCycles  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Eaverage/L/L << "  ";
    ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;
}


void WriteToFileOutputMonteCarlo(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, double Energy){
    /*
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;
    */

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << MonteCarloCycles  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Energy/L/L << endl;
    //ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    //ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    //ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;
}

void WriteToFileOutputMonteSpins(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues, mat SpinMatrix){

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << SpinMatrix  <<endl;
    cout << MonteCarloCycles << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;
}

void WriteAccepted(ofstream& ofile, int MonteCarloCycles, double Accepted_Flips, int L){
    //ofile << "Size of Matrix: " << L << "x" << L << endl;
    //ofile << "|Monte Carlo Cycles|  |Accepted|\n";
    ofile << setprecision(7) << MonteCarloCycles << "   ";
    ofile << setprecision(7) << Accepted_Flips/MonteCarloCycles << endl; 
}

void GenerateTableBottom(ofstream& ofile){
    ofile << "╚═══════════════╧══════════════╧═══════════════╧═══════════════╧════════════════╝\n";
}

void AskForInput(int L, int MonteCarloCycles, int Approach, string SpinConfig){
    ofstream ofile;
    double Temperature; 

    string single_temp = "Singel_Temp.txt";
    string Temp = "Temperature.txt";
    string Monte = "MonteCarloCycles.txt";
    string Spins = "SpinConfig.txt";
    string Accepted = "Accepted_Flips.txt";
    string Reached_Equilibrium = "Data_After_Equilibrium.txt";
    string This_works ="Again.txt";

    if (Approach == 1){
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        ofile.open(single_temp);
        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
        GenerateTableBottom(ofile);
    }
    else if (Approach == 2){
        double initial_temp, final_temp, temp_step;
        cout << "Insert choice of initial temp" << endl;
        cin >> initial_temp;
        cout << "Insert final temperture" << endl;
        cin >> final_temp;
        cout << "Insert temp step" << endl;
        cin >> temp_step;

        ofile.open(Temp);

        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);

        int Int_Temp = initial_temp*10000000;
        int Final_Temp = final_temp*10000000;
        int Temp_Step = temp_step*10000000;

        //cout << omp_get_num_procs() << endl;

        //omp_set_num_threads(4);
        //double StartTime = omp_get_wtime();
        //#pragma omp parallel for
        for (int TempInterval = Int_Temp; TempInterval < Final_Temp; TempInterval+=Temp_Step){
            //Pragma wouldn't for loop for a double so converting to int and then to double again
            // Temp step på 0,0078125
            Temperature = (double) TempInterval/10000000;
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
            cout << "Current Temperature: " << Temperature << endl;
        }
        GenerateTableBottom(ofile);
        //double StopTime = omp_get_wtime();

        //double TotalTime = StopTime-StartTime;
        //cout << "Total Time: " << TotalTime << endl;

    }
    else if (Approach == 3){
        int Equilibrium;
        cout << "Equilibrum MC:" << endl;
        cin >> Equilibrium;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        ofile.open(Reached_Equilibrium);
        GenerateTableTopMonteCarlo(ofile, L, Temperature, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, Equilibrium);
        GenerateTableBottom(ofile);
    }

    // DENNE HER ER KINDA FEIL
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
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        ofile.open(Accepted);

        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, 0);
        GenerateTableBottom(ofile);
    }
    else if (Approach == 6){
        int Equilibrium;
        cout << "Equilibrum MC:" << endl;
        cin >> Equilibrium;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;

        ofile.open(This_works);
        GenerateTableTopMonteCarlo(ofile, L, Temperature, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, Approach, Equilibrium);
        GenerateTableBottom(ofile);
    }
    ofile.close();
}
