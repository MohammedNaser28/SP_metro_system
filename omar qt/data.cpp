
#include "data.h"
using namespace std;
#include <QCoreApplication> // Required for QCoreApplication::applicationDirPath()



void ReadFromFile() {
    ifstream inputfromfile("data of users.txt");
    if (!inputfromfile.is_open()) {
        cerr << "Error: Cannot open 'data of users.txt'" << endl;
        return;
    }

    inputfromfile.ignore(1000, '\n'); // Skip header
    inputfromfile >> number_of_users_in_array;

    for (int i = 0; i < number_of_users_in_array; ++i) {
        inputfromfile >> arr_users[i].username
            >> arr_users[i].id
            >> arr_users[i].admin_role
            >> arr_users[i].balance
            >> arr_users[i].pass
            >> arr_users[i].contactdet.email;
    }

    inputfromfile.close();

    ifstream inputcomplaint("complains.txt");
    if (!inputcomplaint.is_open()) {
        cerr << "Error: Cannot open 'complains.txt'" << endl;
        return;
    }

    inputcomplaint.ignore(1000, '\n'); // Skip header

    for (int i = 0; i < number_of_users_in_array; ++i) {
        string skip1, skip2;
        inputcomplaint >> skip1 >> skip2;
        inputcomplaint.ignore(); // Skip space or newline
        getline(inputcomplaint, arr_users[i].complaints);
    }

    inputcomplaint.close();
}


void saveusersinfo() {
    ofstream outfile_complaints("complains.txt");
    if (!outfile_complaints.is_open()) {
        cerr << "Error: Cannot open 'complains.txt' for writing.\n";
        return;
    }

    outfile_complaints << "The sequence of data is (name---> id ----> complaints)\n\n";

    for (int i = 0; i < number_of_users_in_array; i++) {
        qDebug() << "Checking user:" << QString::fromStdString(arr_users[i].username)
            << "with pass:" << QString::fromStdString(arr_users[i].pass);

        outfile_complaints << arr_users[i].username << " " << arr_users[i].id << " ";

        if (arr_users[i].complaints.empty()) {
            outfile_complaints << "NO COMPLAINTS" << endl;
        }
        else {
            outfile_complaints << arr_users[i].complaints << endl;
        }
    }

    outfile_complaints.close();

    ofstream dataofusers("data of users.txt");
    if (!dataofusers.is_open()) {
        cerr << "Error: Cannot open 'data of users.txt' for writing.\n";
        return;
    }

    dataofusers << "information of person is in this sequence:"
        << "(name --> id --> role --> balance --> password --> email)\n";

    dataofusers << number_of_users_in_array << "\n\n";

    for (int i = 0; i < number_of_users_in_array; i++) {
        const st_of_users& user = arr_users[i];

        dataofusers << user.username << " "
            << user.id << " "
            << user.admin_role << " "
            << user.balance << " "
            << user.pass << " "
            << user.contactdet.email << "\n";
    }

    dataofusers.close();
}


void read_stations() {
    ifstream input_stations("stations.txt");
    if (!input_stations.is_open()) {
        cout << "Error: Could not open stations.txt\n";
        return;
    }

    input_stations.ignore(1000, '\n');

    for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
        for (int j = 0; j < NUM_LINES; j++) {
            input_stations >> allStations[i][j].name;
            if (allStations[i][j].name != "-") {
                num_stations++;
            }
            allStations[i][j].number = (j * MAX_STATIONS_PER_LINE) + (i + 1);
            allStations[i][j].line = j + 1;
        }
    }

    input_stations.close();
}