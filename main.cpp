#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

void displayMenu();
void addParticipant(int id[], string name[], int minute[], double energy[], int& count);
void displayRecord(int id[], string name[], int minute[], double energy[], int count);
int searchParticipant(const int id[], int upper, int target);
void exerciseSummary(string name[], int minute[], double energy[], int count);

const int SIZE = 20;

void displayMenu(){
    /*
    * @brief Display system title and each operations
    */
    cout << "\n+" << string(58, '=') << "+" <<endl;
    cout << "|" << string(6, ' ') << "EXERCISE ENERGY EXPENDITURE MONITORING SYSTEM" << string(7, ' ') << "|" <<endl;
    cout << "+" << string(58, '=') << "+" <<endl;
    cout << "|   [1]  " << left << setw(50) << "Add Participant"      << "|" <<endl;
    cout << "|   [2]  " << left << setw(50) << "Display Records"      << "|" <<endl;
    cout << "|   [3]  " << left << setw(50) << "Search Participant"   << "|" <<endl;
    cout << "|   [4]  " << left << setw(50) << "Print Summary"        << "|" <<endl;
    cout << "|   [5]  " << left << setw(50) << "Exit"                 << "|" <<endl;
    cout << "+" << string(58, '-') << "+" <<endl;
}

void addParticipant(int id[], string name[], int minute[], double energy[], int& i){
    /*
    * @details Add new participant's record, make sure there are no duplicates in id[].
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param i Counter for the function, used & to indicate pass-by-reference
    *          for the function to modify the counter in main
    */
    while (i<SIZE){
        //loop while there are less than 20 records
        double rate;
        int tempID;
        cout << "\n  .--- New Participant " << string(36, '-') <<endl;
        cout << "  | Enter ID number (or -1 to stop)          : ";
        //using tempID before actually append to id[] array 
        //tempID need to be verified to be added when no duplicate is found.
        cin >> tempID;
        if (tempID == -1){
            //terminate the process with an anchor value
            break;
        }
        if (searchParticipant(id, i, tempID) != -1){
            //reusing function searchParticipant() to check for duplicate
            cout << "  '--> [!] Error: The ID already exists! Try a different one.\n";
            //skips the rest of the processes if there are duplicate
            continue;
        }
        id[i] = tempID;
        cout << "  | Enter name                               : ";
        //cleanup any leftover \n from the previous cin in prep for getline()
        cin.ignore();
        getline(cin, name[i]);
        cout << "  | Enter exercise duration (minutes)        : ";
        cin >> minute[i];
        cout << "  | Enter energy expenditure rate (kcal/min) : ";
        cin >> rate;
        //formula for the expended energy
        double expendedEnergy = rate * minute[i];
        energy[i] = expendedEnergy;
        i++;
        cout << "  '--> [OK] Participant " << i << " added to the system.";
        cout <<endl;
    }
    //have another check outside the while loop because the operation might be access after the capacity is full
    if(i>=20){
        cout << "\n  [!] Maximum capacity of 20 participants reached.\n";
    }
}

void displayRecord(int id[], string name[], int minute[], double energy[], int count){
    /*
    * @brief Display all records available.
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param count The length of each array 
    */
    if(count == 0){
        //make sure there are records in array
        cout <<"\n  [!] No records to show.\n";
    }else{
        cout << "\n+" << string(58, '=') << "+" <<endl;
        cout << "|" << string(15, ' ') << "REPORT OF ENERGY EXPENDITURE" << string(15, ' ') << "|" <<endl;
        cout << "+" << string(58, '=') << "+" <<endl;
        for (int i = 0; i <count; i++){
            cout <<fixed <<setprecision(2);
            cout << "| Participant #" <<left <<setw(44) <<i+1 << "|" <<endl;
            cout << "+" << string(58, '-') << "+" <<endl;
            cout << "| " <<left <<setw(32) <<"Participant ID"
                 << ": " <<right <<setw(22) <<id[i] << " |" <<endl;
            cout << "| " <<left <<setw(32) <<"Name of Participant"
                 << ": " <<right <<setw(22) <<name[i] << " |" <<endl;
            cout << "| " <<left <<setw(32) <<"Exercise duration (minutes)"
                 << ": " <<right <<setw(22) <<minute[i] << " |" <<endl;
            cout << "| " <<left <<setw(32) <<"Estimated energy expended (kcal)"
                 << ": " <<right <<setw(22) <<energy[i] << " |" <<endl;
            cout << "+" << string(58, (i == count - 1) ? '=' : '-') << "+" <<endl;
        }
    }
}

int searchParticipant(const int id[], int upper, int target){
    /*
    * @brief Linear search to find the target id's index value
    *
    * @param id The array of participant's IDs
    * @param SIZE Constant of 20, indicating the high boundary
    * @param target The value that needs to be find
    * 
    * @return Index of the target
    */
    for(int i = 0; i < upper; i++){
        if(id[i] == target){
            //iterate through each items in id
            return i;
        }
    }
    //if the loop ended without triggering the return statement, return -1
    //-1 is specifically return because 0 is still an index in array
    return -1;
}

void exerciseSummary(string name[], int minute[], double energy[], int count){
    /*
    * @brief print a summary table with totalDuration, totalEnergy as well as maxEnergy across records
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param count The length of each array
    */
    if (count == 0){
        //make sure there are record in array
        cout <<"\n  [!] Insufficient records to summarise.\n";
    }else{
        int totalDuration = 0, energyIndex = 0;
        double totalEnergy = 0, maxEnergy = energy[0];
        for (int i = 0; i <count; i++){
            //reusing i for each processes
            totalDuration += minute[i];
            totalEnergy += energy[i];
            if (energy[i] > maxEnergy){
                //update value for maxEnergy
                maxEnergy = energy[i];
                //update the index of maxEnergy
                energyIndex = i;
            }
        }
        cout <<fixed<<setprecision(2);
        cout << "\n+" << string(58, '=') << "+" <<endl;
        cout << "|" << string(21, ' ') << "EXERCISE SUMMARY" << string(21, ' ') << "|" <<endl;
        cout << "+" << string(58, '=') << "+" <<endl;
        cout << "| " <<left <<setw(32) <<"Total duration (minutes)"
             << ": " <<right <<setw(22) <<totalDuration << " |" <<endl;
        cout << "| " <<left <<setw(32) <<"Total energy expended (kcal)"
             << ": " <<right <<setw(22) <<totalEnergy << " |" <<endl;
        cout << "| " <<left <<setw(32) <<"Highest energy expended by"
             << ": " <<right <<setw(22) <<name[energyIndex] << " |" <<endl;
        cout << "+" << string(58, '=') << "+" <<endl;
    }
}

int main(){
    //initialising variables and arrays
    int choice = 0, target, count = 0;
    int id[SIZE];
    string name[SIZE];
    int minute[SIZE];
    double energyExpended[SIZE];
    //loop whilst user did not choose 5 (exit)
    while (choice != 5){
        displayMenu();
        cout << "\nPlease select an operation(1-5): ";
        cin >> choice;
        //using switch case for data validation in value 1-5
        switch(choice){
            case 1:
                addParticipant(id, name, minute, energyExpended, count);
                break;
            case 2:
                displayRecord(id, name, minute, energyExpended, count);
                break;
            case 3:{
                //precheck if there are records in the array
                if (count != 0){
                    cout <<"\n  > Enter the Participant's ID: ";
                    cin >> target;
                }else{
                    cout << "\n  [!] Error: no records available to search.\n";
                    break;
                }
                int index = searchParticipant(id, count, target);
                if(index != -1){
                    //print the table if index is found
                    cout <<fixed <<setprecision(2);
                    cout << "\n+" << string(58, '=') << "+" <<endl;
                    cout << "|" << string(22, ' ') << "SEARCH RESULT" << string(23, ' ') << "|" <<endl;
                    cout << "+" << string(58, '=') << "+" <<endl;
                    cout << "| [OK] Participant ID found at index [" << index << "]"
                         << string(20 - to_string(index).length(), ' ') << "|" <<endl;
                    cout << "+" << string(58, '-') << "+" <<endl;
                    cout << "| " <<left <<setw(32) <<"Participant ID"
                         << ": " <<right <<setw(22) <<id[index] << " |" <<endl;
                    cout << "| " <<left <<setw(32) <<"Name of Participant"
                         << ": " <<right <<setw(22) <<name[index] << " |" <<endl;
                    cout << "| " <<left <<setw(32) <<"Exercise duration (minutes)"
                         << ": " <<right <<setw(22) <<minute[index] << " |" <<endl;
                    cout << "| " <<left <<setw(32) <<"Estimated energy expended (kcal)"
                         << ": " <<right <<setw(22) <<energyExpended[index] << " |" <<endl;
                    cout << "+" << string(58, '=') << "+" <<endl;
                }else{
                    cout <<"\n  [!] Participant ID not found in system.\n";
                }
                break;
            }
            case 4:
                exerciseSummary(name, minute, energyExpended, count);
                break;
            case 5:
                cout <<"\n  Thank you for using this program. Goodbye!\n";
                break;
            default:
                cout <<"\n  [!] Invalid selection: please enter a value between 1-5.\n";
        }
    }
    return 0;
}