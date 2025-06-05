#include<iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <utility>
#include <sstream>
#define usersnum 1000
# define Size 10000
using namespace std;//why are you here 

const int MAX_rides = 10000;
const int MAX_STATIONS_PER_LINE = 40;
const int NUM_LINES = 3;
const int MAX = (MAX_STATIONS_PER_LINE * NUM_LINES) * 100;
// alooooool
int stationcnt = 0;
int real_zone;
int balance;
int ride_cnt = 0;
int num_stations = 0; // Total number of stations
int graph[MAX][MAX];
int num_of_subsc;
int kit_kat_index, switching_index;
int arr_sub_insights[1000];


short indexofuser, number_of_users_in_array;
short  hist_rides = 0;


bool DesireToCreateAcc = 1;
bool sign = false;
bool realadmin_by_keypass = false;


string t = "\t\t\t";
string name, password;
string lineshape(50, '_');
string ustars(31, '*');
string uscores(23, '_');
string lineshapeforheader(35, '*');
string subt(100, '-');
string current_user_id;//for saved data in subsc


struct RideInfo {
	string id;
	string entryStation;
	string ExitStation;
	string Date;
	int RideFare;
}rides[MAX_rides];


struct user_subscriptions {
	string subscription_type;
	string expiry;
	string activation;
	string plan_type;
	int Num_trips;
	int duriation_plan_type;
	int remaining_trips;
	string wallet_name;
	int balancew;
	int zonePrice;
	int zone;
	char fixed;
};


struct wallet {
	int card_balance;
	int fund_multiple;
	int zonesPrice[30] = { 0 };
	int zone_num;
};


struct info {
	int duration;
	int no_of_trips;
	int zonesPrice[30] = { 0 };
	int zone_num;


};

struct plan {
	string plan_name;
	string notes;
	char fixed;
	info month_sub[10];
	info year_sub[10];
	int month_count = 0;
	int year_count = 0;
	wallet wallet_sub;

}arr_subscription[20];

struct st_contactdetails {
	string email;
};

struct st_of_users {
	string username;
	string pass;
	string id;
	long long balance;
	user_subscriptions sub;
	bool admin_role;
	st_contactdetails contactdet;
	string complaints;
}newacc;
st_of_users arr_users[usersnum];

struct Station {
	string name;
	int number;
	int line;
	RideInfo rides;
};

Station allStations[MAX_STATIONS_PER_LINE][NUM_LINES]; // 2D array for stations

/// //////////////////////////////////////////////////////////


///////////charge made by aly///////////////
void setActivationDate();
void saveExpiry();
void charge_balance() {
	cout << " \nYou must enter your first balance \n";
	cout << "\n Enter Balance :";
	while (!(cin >> newacc.balance))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << " \nEnter balance correcty :";
	}

	cout << uscores;
}

void recharge() {
	int balance;
	cout << " Please enter the number you want to recharge your balance" << endl;
	cin >> balance;
	arr_users[indexofuser].balance += balance;
}

//---------------------------------nour & haya part -------------------------------//


void finalize_subscription() {

	setActivationDate();
	saveExpiry();
}

/////////////////admin in subscription  ///////////////////

int get_positive_integer() {
	while (true) {
		int n;
		cin >> n;
		if (n > 0) { return n; }
		else { cout << "Please enter a positive integer" << endl; }
	}
}

char get_y_n() {
	char n;
	while (true) {
		cin >> n;
		if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
			return n;
		}
		else { cout << "Invalid input. Please enter (y/n)" << endl; }
	}
}

void edit_monthly(int edited_sub) {
	char zone_answer;
	int change2;
	for (int i = 0; i < arr_subscription[edited_sub].month_count; i++) {
		cout << "Do you want to edit monthly plan #" << i + 1 << "(y/n)?" << endl;
		char ans1 = get_y_n();
		if (ans1 == 'y' || ans1 == 'Y') {
			do {
				cout << "What do you want to change in your monthly plan? " << endl;
				cout << "1-Duration" << endl;
				cout << "2-Number of trips" << endl;
				cout << "3-Number of zones" << endl;
				cout << "4-Zones Price" << endl;
				cout << "5-Exit" << endl;
				change2 = get_positive_integer();

				switch (change2) {
				case 1:
					cout << "Enter duration (months): ";
					arr_subscription[edited_sub].month_sub[i].duration = get_positive_integer();
					break;
				case 2:
					cout << "Enter number of trips: ";
					arr_subscription[edited_sub].month_sub[i].no_of_trips = get_positive_integer();
					break;
				case 3:
					cout << "Enter number of zones: ";
					arr_subscription[edited_sub].month_sub[i].zone_num = get_positive_integer();
					for (int j = 0; j < arr_subscription[edited_sub].month_sub[i].zone_num; j++) {
						cout << "Enter price for Zone " << j + 1 << ": ";
						arr_subscription[edited_sub].month_sub[i].zonesPrice[j] = get_positive_integer();
					}
					break;
				case 4: {
					int n;
					do {
						cout << "This monthly plan have " << arr_subscription[edited_sub].month_sub[i].zone_num << " zones" << endl;
						cout << "Please enter the zone number" << endl;
						n = get_positive_integer();
						cout << "Enter Price for zone " << n << endl;
						arr_subscription[edited_sub].month_sub[i].zonesPrice[n - 1] = get_positive_integer();
						cout << "Do you want to change the price for another zone?(y/n)" << endl;
						zone_answer = get_y_n();
					} while (zone_answer == 'y' || zone_answer == 'Y');
					break;
				}
				case 5:
					cout << "Exiting" << endl;
					break;
				default:
					cout << "Invalid option please try again" << endl;
					break;
				}
			} while (change2 != 5);
		}
	}
}

void edit_yearly(int edited_sub) {
	int change2;
	for (int i = 0; i < arr_subscription[edited_sub].year_count; i++) {
		cout << "Do you want to edit yearly plan #" << i + 1 << "(y/n)?" << endl;
		char ans1 = get_y_n();
		if (ans1 == 'y' || ans1 == 'Y') {
			do {
				cout << "What do you want to change in your yearly plan? " << endl;
				cout << "1-Duration" << endl;
				cout << "2-Number of trips" << endl;
				cout << "3-Number of zones" << endl;
				cout << "4-Zones Price" << endl;
				cout << "5-Exit" << endl;
				change2 = get_positive_integer();
				switch (change2) {
				case 1:
					cout << "Enter duration (months): ";
					arr_subscription[edited_sub].year_sub[i].duration = get_positive_integer();
					break;
				case 2:
					cout << "Enter number of trips: ";
					arr_subscription[edited_sub].year_sub[i].no_of_trips = get_positive_integer();
					break;
				case 3:
					cout << "Enter number of zones: ";
					arr_subscription[edited_sub].year_sub[i].zone_num = get_positive_integer();
					for (int j = 0; j < arr_subscription[edited_sub].year_sub[i].zone_num; j++) {
						cout << "Enter price for Zone " << j + 1 << ": ";
						arr_subscription[edited_sub].year_sub[i].zonesPrice[j] = get_positive_integer();
					}
					break;
				case 4: {
					int n;
					char zone_answer;
					do {
						cout << "This yearly plan have " << arr_subscription[edited_sub].year_sub[i].zone_num << " zones" << endl;
						cout << "Please enter the zone number" << endl;
						n = get_positive_integer();
						cout << "Enter Price for zone " << n << endl;
						arr_subscription[edited_sub].year_sub[i].zonesPrice[n - 1] = get_positive_integer();
						cout << "Do you want to change the price for another zone?(y/n)" << endl;
						zone_answer = get_y_n();
					} while (zone_answer == 'y' || zone_answer == 'Y');
					break;
				}
				case 5:
					cout << "Exiting" << endl;
					break;
				default:
					cout << "Invalid option please try again" << endl;
					break;
				}
			} while (change2 != 5);
		}
	}
}

void modify(int num_of_subsc) {
	//modify
	int edited_sub;
	if (num_of_subsc == 0) {
		cout << "No subscriptions to edit.";
	}
	else {
		for (int i = 0; i < num_of_subsc; i++) {
			cout << i + 1 << "- " << arr_subscription[i].plan_name << endl;
		}
		cout << "Enter the number of the subscription plan you want to edit: ";
		cin >> edited_sub;
		cin.ignore();
		edited_sub -= 1;

		if (arr_subscription[edited_sub].fixed == 'y') {
			int change;
			do {
				cout << "What do you want to change in your subscription?" << endl;
				cout << "1-Subscription name" << endl;
				cout << "2-Monthly plans" << endl;
				cout << "3-Yearly plans" << endl;
				cout << "4-Notes" << endl;
				cout << "5-Exit" << endl;
				change = get_positive_integer();
				cin.ignore();
				switch (change) {
				case 1:
					cout << "Enter new name: ";
					getline(cin, arr_subscription[edited_sub].plan_name);
					break;
				case 2:
					edit_monthly(edited_sub);
					break;
				case 3:
					edit_yearly(edited_sub);
					break;
				case 4:
					cout << "Please enter your new notes: " << endl;
					getline(cin, arr_subscription[edited_sub].notes);
					break;
				case 5:
					cout << "Subscription edited successfully!" << endl;
					break;
				default:
					cout << "Invalid option please try again" << endl;
					break;
				}
			} while (change != 5);
		}
		else if (arr_subscription[edited_sub].fixed == 'n') {
			int change;
			do {
				cout << "What do you want to change in your wallet?" << endl;
				cout << "1-Wallet name" << endl;
				cout << "2-Max card balance" << endl;
				cout << "3-Fund multiple" << endl;
				cout << "4-Number of zones" << endl;
				cout << "5-Zones Price" << endl;
				cout << "6-Notes" << endl;
				cout << "7-Exit" << endl;
				change = get_positive_integer();
				cin.ignore();
				switch (change) {
				case 1:
					cout << "Enter new name: ";
					getline(cin, arr_subscription[edited_sub].plan_name);
					break;
				case 2:
					cout << "Enter new max card balance: " << endl;
					arr_subscription[edited_sub].wallet_sub.card_balance = get_positive_integer();
					break;
				case 3:
					cout << "Enter new fund multiple: " << endl;
					arr_subscription[edited_sub].wallet_sub.fund_multiple = get_positive_integer();
					break;
				case 4:
					cout << "Enter new number of zones: ";
					arr_subscription[edited_sub].wallet_sub.zone_num = get_positive_integer();
					break;
				case 5:
					cout << "Please enter the zone number " << endl;
					int z;
					z = get_positive_integer();
					cout << "Enter price for Zone " << z << ": ";
					arr_subscription[edited_sub].wallet_sub.zonesPrice[z - 1] = get_positive_integer();
					break;
				case 6:
					cout << "Please enter your new notes: " << endl;
					getline(cin, arr_subscription[edited_sub].notes);
					break;
				case 7:
					cout << "Subscription edited successfully!" << endl;
					break;
				default:
					cout << "Invalid option please try again" << endl;
					break;
				}
			} while (change != 7);
		}
	}
}

void view(int num_of_subsc) {

	if (num_of_subsc == 0) { cout << "No available subscriptions" << endl; }
	else {
		cout << "* There are many options, choose what suits you * " << endl;
		for (int i = 0;i < num_of_subsc;i++) {
			/*if (arr_subscription[i].plan_name == "")
				break;*/
			cout << "\t*" << i + 1 << "-" << arr_subscription[i].plan_name << endl;
			if (arr_subscription[i].fixed == 'y') {//problem fixed will always b false in sec. run
				cout << "Fixed Payment every ";
				for (int j = 0;j < arr_subscription[i].month_count;j++) {//error month count will always = 0 in sec. run
					cout << arr_subscription[i].month_sub[j].duration << " months for " << arr_subscription[i].month_sub[j].no_of_trips << " trips with limited stations access" << endl;
					for (int k = 0;k < arr_subscription[i].month_sub[j].zone_num;k++) {
						cout << "For Zone " << k + 1 << " : " << arr_subscription[i].month_sub[j].zonesPrice[k] << " LE" << "  " << endl;
					}
					cout << endl;
				}
				for (int j = 0;j < arr_subscription[i].year_count;j++) {

					cout << arr_subscription[i].year_sub[j].duration << " years for " << arr_subscription[i].year_sub[j].no_of_trips << " trips with limited stations access" << endl;
					for (int k = 0;k < arr_subscription[i].year_sub[j].zone_num;k++) {
						cout << "For Zone " << k + 1 << " : " << arr_subscription[i].year_sub[j].zonesPrice[k] << " LE" << "  " << endl;
					}
					cout << endl;
				}
				cout << ustars << endl;

			}
			else if (arr_subscription[i].fixed == 'n')
			{
				cout << "You can add funds in multiples of " << arr_subscription[i].wallet_sub.fund_multiple << " LE at any time" << endl;
				cout << "The card balance cannot exceed " << arr_subscription[i].wallet_sub.card_balance << " LE" << endl;
				cout << "No time restrictions" << endl;
				cout << "Zones prices" << endl;
				for (int k = 0;k < arr_subscription[i].wallet_sub.zone_num;k++) {
					cout << "For Zone " << k + 1 << " : " << arr_subscription[i].wallet_sub.zonesPrice[k] << " LE" << "  " << endl;

				}

			}
			cout << endl;
			cout << arr_subscription[i].notes << endl;

		}
	}
}

void add(int& num_of_subsc) {
	char x = '\0', z, choice, choice2;
	int i = num_of_subsc;

	do {
		int month_index = 0;
		int year_index = 0;
		cout << "Add New Subscription Plan" << endl;
		do {
			cout << "Please enter subscription plan name: ";
			getline(cin, arr_subscription[i].plan_name);
			if (arr_subscription[i].plan_name.empty()) {
				cout << "Plan name cannot be empty.\n";
			}
		} while (arr_subscription[i].plan_name.empty());

		cout << "Do you want the payment fixed ?(y/n)" << endl;
		char ans;
		ans = get_y_n();
		cin.ignore();
		if (ans == 'y' || ans == 'Y') {
			arr_subscription[i].fixed = 'y';
			cout << "Do you want to add a monthly plan? (y/n) " << endl;
			choice = get_y_n();
			cin.ignore();
			if (choice == 'y' || choice == 'Y') {
				do {
					cout << "How many months will this plan be?" << endl;
					arr_subscription[i].month_sub[month_index].duration = get_positive_integer();
					cout << "Please enter number of trips allowed?" << endl;
					arr_subscription[i].month_sub[month_index].no_of_trips = get_positive_integer();
					cout << "How many zones?" << endl;
					int n;
					n = get_positive_integer();
					cin.ignore();
					arr_subscription[i].month_sub[month_index].zone_num = n;
					for (int j = 0;j < n;j++) {
						cout << "Please price of Zone " << j + 1 << endl;
						arr_subscription[i].month_sub[month_index].zonesPrice[j] = get_positive_integer();
					}
					month_index++;
					arr_subscription[i].month_count = month_index;
					cout << "Do you want to add another month plan in this subscription?(y/n)" << endl;
					z = get_y_n();
					cin.ignore();
				} while (z == 'y' || z == 'Y');
			}

			cout << "Do you want to add a yearly plan? (y/n)" << endl;
			choice2 = get_y_n();
			cin.ignore();
			if (choice2 == 'y' || choice2 == 'Y') {
				do {
					cout << "How many years will this plan be?" << endl;
					arr_subscription[i].year_sub[year_index].duration = get_positive_integer();
					cout << "Please enter number of trips allowed?" << endl;
					arr_subscription[i].year_sub[year_index].no_of_trips = get_positive_integer();
					cout << "How many zones?" << endl;
					int n;
					n = get_positive_integer();
					cin.ignore();
					arr_subscription[i].year_sub[year_index].zone_num = n;
					for (int j = 0;j < n;j++) {
						cout << "Please price of Zone " << j + 1 << endl;
						arr_subscription[i].year_sub[year_index].zonesPrice[j] = get_positive_integer();
					}
					year_index++;
					arr_subscription[i].year_count = year_index;
					cout << "Do you want to add another year plan in this subscription?(y/n)" << endl;
					z = get_y_n();
					cin.ignore();
				} while (z == 'y' || z == 'Y');
			}
			cout << "Add any notes about this subscription(press enter to skip)" << endl;
			getline(cin, arr_subscription[i].notes);

		}
		else if (ans == 'n' || ans == 'N') {
			arr_subscription[i].fixed = 'n';
			cout << "Wallet subscription" << endl;
			cout << "Please enter max card balance " << endl;
			cin >> arr_subscription[i].wallet_sub.card_balance;
			cout << "Please enter the fund multiple" << endl;
			cin >> arr_subscription[i].wallet_sub.fund_multiple;
			cout << "How many zones?" << endl;
			int n;
			n = get_positive_integer();
			cin.ignore();
			arr_subscription[i].wallet_sub.zone_num = n;
			for (int j = 0;j < n;j++) {
				cout << "Please price of Zone " << j + 1 << endl;
				arr_subscription[i].wallet_sub.zonesPrice[j] = get_positive_integer();
			}
			cout << "Add any notes about this subscription(press enter to skip)" << endl;
			cin.ignore();
			getline(cin, arr_subscription[i].notes);


		}
		i++;
		num_of_subsc++;

		cout << "Do you want to add a new subscription plan?" << endl;
		cin >> x;
		cin.ignore();

	} while (x == 'y' || x == 'Y');

}

void delete_sub(int& num_of_subsc) {
	//delete
	for (int i = 0;i < 20;i++) {
		if (arr_subscription[i].plan_name == "")break;
		cout << i + 1 << "-" << arr_subscription[i].plan_name << endl;
	}
	cout << "Enter the number of the subscription plan you want to delete: " << endl;
	int deleted_sub;
	cin >> deleted_sub;
	cin.ignore();
	deleted_sub -= 1;
	cout << "Are you sure you want to delete (" << arr_subscription[deleted_sub].plan_name << ") ? (y/n): ";
	char confirm;
	confirm = get_y_n();
	cin.ignore();
	if (confirm == 'y' || confirm == 'Y') {
		for (int i = deleted_sub; i < num_of_subsc - 1; ++i) {
			arr_subscription[i] = arr_subscription[i + 1];
		}
		cout << "Subscription deleted successfully" << endl;
		arr_subscription[num_of_subsc - 1] = {};  // Clear last element
		num_of_subsc--;
	}
	else { cout << "Deletion Cancelled" << endl; }


}

void save_subsc_data() {
	ofstream file("subsc data.txt");
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	file << num_of_subsc << endl;

	for (int i = 0; i < num_of_subsc; i++) {
		if (arr_subscription[i].fixed == 'y') {

			file << arr_subscription[i].plan_name << endl;
			file << arr_subscription[i].fixed << endl;

			file << arr_subscription[i].month_count << endl;
			for (int j = 0; j < arr_subscription[i].month_count; j++) {
				file << arr_subscription[i].month_sub[j].duration << "   "
					<< arr_subscription[i].month_sub[j].no_of_trips << "   "
					<< arr_subscription[i].month_sub[j].zone_num << "   ";
				for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
					file << arr_subscription[i].month_sub[j].zonesPrice[k] << "   ";
				}
				file << endl;
			}

			file << arr_subscription[i].year_count << endl;
			for (int j = 0; j < arr_subscription[i].year_count; j++) {
				file << arr_subscription[i].year_sub[j].duration << "   "
					<< arr_subscription[i].year_sub[j].no_of_trips << "   "
					<< arr_subscription[i].year_sub[j].zone_num << "   ";
				for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
					file << arr_subscription[i].year_sub[j].zonesPrice[k] << "   ";
				}
				file << endl;
			}

			file << arr_subscription[i].notes << endl;
		}
		else if (arr_subscription[i].fixed == 'n') {

			file << arr_subscription[i].plan_name << endl
				<< arr_subscription[i].fixed << endl
				<< arr_subscription[i].wallet_sub.card_balance << "   "
				<< arr_subscription[i].wallet_sub.fund_multiple << "   "
				<< arr_subscription[i].wallet_sub.zone_num << "   ";
			for (int k = 0;k < arr_subscription[i].wallet_sub.zone_num;k++) {
				file << arr_subscription[i].wallet_sub.zonesPrice[k] << "   ";

			}
			file << endl;
			file << arr_subscription[i].notes << "   " << endl;


		}
	}

	file.close();
}

void load_subsc_data() {
	ifstream file("subsc data.txt");
	if (!file) {
		cout << "No subscription data found!" << endl;
		return;
	}

	file >> num_of_subsc;

	for (int i = 0; i < num_of_subsc; i++) {

		file >> arr_subscription[i].plan_name;
		file >> arr_subscription[i].fixed;

		if (arr_subscription[i].fixed == 'y') {

			file >> arr_subscription[i].month_count;
			for (int j = 0; j < arr_subscription[i].month_count; j++) {
				file >> arr_subscription[i].month_sub[j].duration
					>> arr_subscription[i].month_sub[j].no_of_trips
					>> arr_subscription[i].month_sub[j].zone_num;
				for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
					file >> arr_subscription[i].month_sub[j].zonesPrice[k];
				}
			}
			file >> arr_subscription[i].year_count;
			for (int j = 0; j < arr_subscription[i].year_count; j++) {
				file >> arr_subscription[i].year_sub[j].duration
					>> arr_subscription[i].year_sub[j].no_of_trips
					>> arr_subscription[i].year_sub[j].zone_num;
				for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
					file >> arr_subscription[i].year_sub[j].zonesPrice[k];
				}
			}

			getline(file, arr_subscription[i].notes);
		}
		else if (arr_subscription[i].fixed == 'n')
		{

			file
				>> arr_subscription[i].wallet_sub.card_balance
				>> arr_subscription[i].wallet_sub.fund_multiple
				>> arr_subscription[i].wallet_sub.zone_num;
			for (int k = 0;k < arr_subscription[i].wallet_sub.zone_num;k++) {
				file >> arr_subscription[i].wallet_sub.zonesPrice[k];

			}
			getline(file, arr_subscription[i].notes);


		}

	}

	file.close();
}

string getCurrentDate() {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);

	struct tm timeinfo;
	localtime_s(&timeinfo, &now_time);

	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d/%m/%Y", &timeinfo);
	return string(buffer);
}

//////nour func for user subsc //////

void view_subsc_user() {

	if (num_of_subsc == 0) {
		cout << "No available subscriptions" << endl;
	}
	else {
		cout << "\n* There are many options, choose what suits you *\n " << endl;
		for (int i = 0;i < num_of_subsc;i++) {
			int numbers = 1;
			cout << "\t*" << i + 1 << "-" << arr_subscription[i].plan_name << endl;
			if (arr_subscription[i].fixed == 'y') {//problem fixed will always b false in sec. run
				cout << numbers << " - " << "Fixed Payment every ";

				for (int j = 0;j < arr_subscription[i].month_count;j++) {//error month count will always = 0 in sec. run
					cout << arr_subscription[i].month_sub[j].duration << " months for " << arr_subscription[i].month_sub[j].no_of_trips << " trips with limited stations access" << endl;
					for (int k = 0;k < arr_subscription[i].month_sub[j].zone_num;k++) {
						cout << "For Zone " << k + 1 << " : " << arr_subscription[i].month_sub[j].zonesPrice[k] << " LE" << "  " << endl;
					}
					cout << endl;
					numbers++;
				}
				for (int j = 0;j < arr_subscription[i].year_count;j++) {

					cout << numbers << " - " << arr_subscription[i].year_sub[j].duration << " years for " << arr_subscription[i].year_sub[j].no_of_trips << " trips with limited stations access" << endl;
					for (int k = 0;k < arr_subscription[i].year_sub[j].zone_num;k++) {
						cout << "For Zone " << k + 1 << " : " << arr_subscription[i].year_sub[j].zonesPrice[k] << " LE" << "  " << endl;
					}
					cout << endl;
					numbers++;
				}
				cout << ustars << endl;

			}
			else if (arr_subscription[i].fixed == 'n')
			{
				cout << "You can add funds in multiples of " << arr_subscription[i].wallet_sub.fund_multiple << " LE at any time" << endl;
				cout << "The card balance cannot exceed " << arr_subscription[i].wallet_sub.card_balance << " LE" << endl;
				cout << "No time restrictions" << endl;
				cout << "Zones prices" << endl;
				for (int k = 0;k < arr_subscription[i].wallet_sub.zone_num;k++) {
					cout << "For Zone " << k + 1 << " : " << arr_subscription[i].wallet_sub.zonesPrice[k] << " LE" << "  " << endl;
				}
				cout << ustars << endl;
				break;
			}
		}
	}
}

void user_choice() {
	int sub_type;
	int numbers = 1;
	bool month = false;
	bool year = false;
	int planvar;
	int zone_var;
	int fund;
	bool flag = true, sub = false, plan = false, zone = false, wallet = false;

	while (!sub) {
		cout << "Please enter your subscription" << endl;
		cin >> sub_type;
		if (sub_type <= num_of_subsc) {
			sub = true;
			for (int i = 0;i < num_of_subsc;i++) {
				if ((sub_type - 1) == i) {
					newacc.sub.subscription_type = arr_subscription[i].plan_name;
					newacc.sub.fixed = arr_subscription[i].fixed;
					break;
				}
			}
		}
		else {
			cout << "Invalid!!" << endl;
		}
	}
	int month_count = arr_subscription[sub_type - 1].month_count;
	int year_count = arr_subscription[sub_type - 1].year_count;
	int total_plans = month_count + year_count;
	while (!plan && ((newacc.sub.fixed) == 'y')) {
		//for initialize the wallet by 0 for the file
		newacc.sub.balancew = 0;
		newacc.sub.wallet_name = "0";


		cout << "\nChoose your suitable plan ( 1 to " << total_plans << "): ";
		cin >> planvar;
		if (planvar < 1 || planvar > total_plans) {
			cout << "Invalid plan number! Please try again." << endl;
			continue;

		}
		else if (planvar >= 1 && planvar <= month_count) {



			plan = true;
			month = true;
			newacc.sub.plan_type = "month";
			newacc.sub.duriation_plan_type = arr_subscription[sub_type - 1].month_sub[planvar - 1].duration;
			newacc.sub.Num_trips = arr_subscription[sub_type - 1].month_sub[planvar - 1].no_of_trips;
			newacc.sub.remaining_trips = newacc.sub.Num_trips;
			break;

		}

		else if (planvar > month_count && planvar <= total_plans) {
			int yearindex = (planvar - arr_subscription[sub_type - 1].month_count) - 1;
			plan = true;
			year = true;
			newacc.sub.plan_type = "year";
			newacc.sub.duriation_plan_type = arr_subscription[sub_type - 1].year_sub[yearindex].duration;
			newacc.sub.Num_trips = arr_subscription[sub_type - 1].year_sub[yearindex].no_of_trips;
			newacc.sub.remaining_trips = newacc.sub.Num_trips;
			break;


		}

		break;
	}
	////////////////wallet//////////////////////
	while (!plan && ((newacc.sub.fixed) == 'n')) {

		planvar = 0;

		if (((newacc.sub.fixed) == 'n')) {
			plan = true;
			wallet = true;
			//for initialize the subscription by 0 for the file
			newacc.sub.duriation_plan_type = 0;
			newacc.sub.Num_trips = 0;
			newacc.sub.expiry = "0";


			cout << "Your subscription is : " << arr_subscription[sub_type - 1].plan_name << endl;
			cout << "Please enter your desired fund" << endl;
			while (flag) {
				cin >> fund;
				if (fund % (arr_subscription[sub_type - 1].wallet_sub.fund_multiple) == 0) {
					newacc.sub.balancew += fund;
					if (newacc.sub.balancew <= arr_subscription[sub_type - 1].wallet_sub.card_balance) {
						newacc.balance -= newacc.sub.balancew;

						cout << "\nYou have charged your Wallet Balance by : " << newacc.sub.balancew << endl;
						cout << "\nYour current balance :" << newacc.balance << endl;
						flag = false;
					}
					else {
						newacc.sub.balancew -= fund;
						cout << "Please enter fund less than the maximum charge" << endl;
					}


				}
				else if (fund % (arr_subscription[sub_type - 1].wallet_sub.fund_multiple) != 0) {
					cout << " You must put a value in multiple of " << arr_subscription[sub_type - 1].wallet_sub.fund_multiple << endl;
					continue;
				}

			}

		}
	}
	//////////////////////////////////////////////////////////////////////////
	int yearindex = (planvar - arr_subscription[sub_type - 1].month_count) - 1;

	while (!zone) {
		int charge;
		if (month) {
			int zone_num = arr_subscription[sub_type - 1].month_sub[planvar - 1].zone_num;
			for (int j = 0;j < zone_num;j++) {
				cout << "For Zone " << j + 1
					<< " : "
					<< arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[j]
					<< " LE" << "  ";
			}
			cout << " Please choose your zone \n";
			cin >> zone_var;
			cin.ignore();
			if (zone_var <= zone_num) {
				zone = true;
				if ((newacc.balance - arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1] < 0)) {
					cout << "No enough balance to renew, please recharge" << endl;
					cout << "1-Recharge now" << endl;
					cout << "2-Exit" << endl;
					charge = get_positive_integer();
					switch (charge) {
					case 1:
						charge_balance();
						break;
					case 2:
						break;
					}

				}

				else {
					newacc.sub.zone = zone_var;
					newacc.sub.zonePrice = arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1];
					newacc.balance -= newacc.sub.zonePrice;

					cout << endl;
					cout << "you have choosen -->  ";
					cout << "Zone " << newacc.sub.zone << ":" << "for" << newacc.sub.zonePrice << "LE" << endl;
					cout << "your current balance :" << newacc.balance << endl;
					break;
				}

			}
		}

		else if (year) {

			int zone_num = arr_subscription[sub_type - 1].year_sub[yearindex].zone_num;
			cout << " Please choose your zone \n";
			for (int j = 0;j < zone_num;j++) {
				cout << "For Zone " << j + 1
					<< " : "
					<< arr_subscription[sub_type - 1].year_sub[yearindex].zonesPrice[j]
					<< " LE" << "  ";
			}
			cout << endl;
			cin >> zone_var;
			cin.ignore();
			if (zone_var <= zone_num) {
				zone = true;
				if ((newacc.balance - arr_subscription[sub_type - 1].year_sub[yearindex].zonesPrice[zone_var - 1] < 0)) {
					cout << "No enough balance to renew, please recharge" << endl;
					cout << "1-Recharge now" << endl;
					cout << "2-Exit" << endl;
					charge = get_positive_integer();
					switch (charge) {
					case 1:
						charge_balance();
						break;
					case 2:
						break;
					}

				}

				else {


					cout << "you have choosen  --> ";

					newacc.sub.zone = zone_var;
					newacc.sub.zonePrice = arr_subscription[sub_type - 1].year_sub[yearindex].zonesPrice[zone_var - 1];
					newacc.balance -= newacc.sub.zonePrice;
					cout << "Zone " << newacc.sub.zone << ":" << "for" << newacc.sub.zonePrice << "LE" << endl;
					cout << "your current balance: " << newacc.balance;
					break;
				}
			}
		}

		else if (wallet) {
			zone = true;
		}
		else {
			cout << "Your choise is not available " << endl;
		}
	}

}

int not_fixed(int station_num) {
	int fare;
	for (int i = 0;i < num_of_subsc;i++) {
		int zone = 0;
		if (station_num <= 9) {
			zone = 1;

		}
		else if (station_num > 9 && station_num <= 16) {

			zone = 2;
		}
		else if (station_num > 16 && station_num <= 23) {
			zone = 3;
		}
		else {
			zone = 4;
		}


		if (arr_users[indexofuser].sub.subscription_type == arr_subscription[i].plan_name) {
			if (station_num <= 9) {
				arr_users[indexofuser].sub.balancew -= arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
				fare = arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
			}
			else if (station_num > 9 && station_num <= 16) {
				arr_users[indexofuser].sub.balancew -= arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
				fare = arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
			}
			else if (station_num > 16 && station_num <= 23) {
				arr_users[indexofuser].sub.balancew -= arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
				fare = arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
			}
			else {
				arr_users[indexofuser].sub.balancew -= arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
				fare = arr_subscription[i].wallet_sub.zonesPrice[zone - 1];
			}
		}
	}

	return fare;
}

void choose_again() {
	int sub_type;
	int numbers = 1;
	bool month = false;
	bool year = false;
	int planvar;
	int zone_var;
	int fund;
	bool flag = true, sub = false, plan = false, zone = false, wallet = false;
	for (int i = 0;i < num_of_subsc;i++) {

		if (arr_subscription[i].fixed == 'n')
		{

			cout << "You can add funds in multiples of " << arr_subscription[i].wallet_sub.fund_multiple << " LE at any time" << endl;
			cout << "The card balance cannot exceed " << arr_subscription[i].wallet_sub.card_balance << " LE" << endl;
			cout << "No time restrictions" << endl;
			cout << "Zones prices" << endl;
			for (int k = 0;k < arr_subscription[i].wallet_sub.zone_num;k++) {
				cout << "For Zone " << k + 1 << " : " << arr_subscription[i].wallet_sub.zonesPrice[k] << " LE" << "  ";
			}
			break;
		}
	}

	while (!sub) {
		cout << "Please enter your subscription" << endl;
		cin >> sub_type;
		if (sub_type <= num_of_subsc) {
			sub = true;
			for (int i = 0;i < num_of_subsc;i++) {
				if ((sub_type - 1) == i) {
					arr_users[indexofuser].sub.subscription_type = arr_subscription[i].plan_name;
					arr_users[indexofuser].sub.fixed = arr_subscription[i].fixed;
					break;
				}
			}
		}
		else {
			cout << "Invalid!!" << endl;
		}
	}
	int month_count = arr_subscription[sub_type - 1].month_count;
	int year_count = arr_subscription[sub_type - 1].year_count;
	int total_plans = month_count + year_count;
	while (!plan && ((arr_users[indexofuser].sub.fixed) == 'y')) {
		cout << "\nChoose your suitable plan ( 1 to " << total_plans << "): ";
		cin >> planvar;
		if (planvar < 1 || planvar > total_plans) {
			cout << "Invalid plan number! Please try again." << endl;
			continue;

		}
		else if (planvar >= 1 && planvar <= month_count && ((arr_users[indexofuser].sub.fixed) == 'y')) {

			//for initialize the wallet by 0 for the file
			arr_users[indexofuser].sub.balancew = 0;
			arr_users[indexofuser].sub.wallet_name = "0";


			plan = true;
			month = true;
			arr_users[indexofuser].sub.plan_type = "month";
			arr_users[indexofuser].sub.duriation_plan_type = arr_subscription[sub_type - 1].month_sub[planvar - 1].duration;
			arr_users[indexofuser].sub.Num_trips = arr_subscription[sub_type - 1].month_sub[planvar - 1].no_of_trips;
			arr_users[indexofuser].sub.remaining_trips = arr_users[indexofuser].sub.Num_trips;
			break;

		}

		else if (planvar > month_count && planvar <= total_plans && ((arr_users[indexofuser].sub.fixed) == 'y')) {
			int yearindex = (planvar - arr_subscription[sub_type - 1].month_count) - 1;
			plan = true;
			year = true;
			arr_users[indexofuser].sub.plan_type = "year";
			arr_users[indexofuser].sub.duriation_plan_type = arr_subscription[sub_type - 1].year_sub[yearindex].duration;
			arr_users[indexofuser].sub.Num_trips = arr_subscription[sub_type - 1].year_sub[yearindex].no_of_trips;
			arr_users[indexofuser].sub.remaining_trips = arr_users[indexofuser].sub.Num_trips;
			break;



		}
		finalize_subscription();

		break;
	}

	while (!plan && ((arr_users[indexofuser].sub.fixed) == 'n')) {
		planvar = 0;

		if (((arr_users[indexofuser].sub.fixed) == 'n')) {
			plan = true;
			wallet = true;
			//for initialize the subscription by 0 for the file
			arr_users[indexofuser].sub.duriation_plan_type = 0;
			arr_users[indexofuser].sub.Num_trips = 0;
			setActivationDate();
			arr_users[indexofuser].sub.plan_type = arr_subscription[sub_type - 1].plan_name;
			cout << "Your subscription is : " << arr_subscription[sub_type - 1].plan_name << endl;
			cout << "Please enter your desired fund" << endl;
			while (flag) {
				cin >> fund;

				if (arr_users[indexofuser].balance >= fund) {
					if (fund % (arr_subscription[sub_type - 1].wallet_sub.fund_multiple) == 0) {
						arr_users[indexofuser].sub.balancew += fund;
						if (arr_users[indexofuser].sub.balancew <= arr_subscription[sub_type - 1].wallet_sub.card_balance) {
							arr_users[indexofuser].balance -= arr_subscription[sub_type - 1].wallet_sub.card_balance;

							cout << "\nYou have charged your Wallet Balance by : " << arr_subscription[sub_type - 1].wallet_sub.card_balance << endl;
							cout << "\nYour current balance :" << arr_users[indexofuser].balance << endl;
							flag = false;
						}
						else {
							arr_users[indexofuser].sub.balancew -= fund;
							cout << "Please enter fund less than the maximum charge" << endl;
						}
					}
				}
				else {
					cout << "your balance is not enough please recharge" << endl;
					recharge();
					continue;
				}
			
			
			
			}

		}
	}
	int yearindex = (planvar - arr_subscription[sub_type - 1].month_count) - 1;

	while (!zone) {

		if (month) {
			int zone_num = arr_subscription[sub_type - 1].month_sub[planvar - 1].zone_num;
			for (int j = 0;j < zone_num;j++) {
				cout << "For Zone " << j + 1
					<< " : "
					<< arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[j]
					<< " LE" << "  ";
			}
			cout << " Please choose your zone \n";
			cin >> zone_var;
			cin.ignore();
			if (zone_var <= zone_num) {
				zone = true;
				cout << endl;
				cout << "you have choosen -->  ";
				arr_users[indexofuser].sub.zone = zone_var;
				arr_users[indexofuser].sub.zonePrice = arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1];
				arr_users[indexofuser].balance -= arr_users[indexofuser].sub.zonePrice;
				cout << "Zone " << arr_users[indexofuser].sub.zone << ":" << "for" << arr_users[indexofuser].sub.zonePrice << "LE" << endl;
				cout << "your current balance :" << arr_users[indexofuser].balance << endl;
				break;

			}
		}

		else if (year) {

			int zone_num = arr_subscription[sub_type - 1].year_sub[yearindex].zone_num;
			cout << " Please choose your zone \n";
			for (int j = 0;j < zone_num;j++) {
				cout << "For Zone " << j + 1
					<< " : "
					<< arr_subscription[sub_type - 1].year_sub[yearindex].zonesPrice[j]
					<< " LE" << "  ";
			}
			cout << endl;
			cin >> zone_var;
			cin.ignore();
			if (zone_var <= zone_num) {
				zone = true;
				cout << "you have choosen  --> ";

				arr_users[indexofuser].sub.zone = zone_var;
				arr_users[indexofuser].sub.zonePrice = arr_subscription[sub_type - 1].year_sub[yearindex].zonesPrice[zone_var - 1];
				arr_users[indexofuser].balance -= arr_users[indexofuser].sub.zonePrice;
				cout << "Zone " << arr_users[indexofuser].sub.zone << ":" << "for" << arr_users[indexofuser].sub.zonePrice << "LE" << endl;
				cout << "your current balance: " << arr_users[indexofuser].balance;
				break;
			}
		}

		else if (wallet) {
			int zone_num = arr_subscription[sub_type - 1].wallet_sub.zone_num;
			for (int j = 0;j < zone_num;j++) {
				cout << "For Zone " << j + 1
					<< " : "
					<< arr_subscription[sub_type - 1].wallet_sub.zonesPrice[j]
					<< " LE" << "  ";
			}
			cout << " Please choose your zone \n";
			cin >> zone_var;
			cin.ignore();
			if (zone_var <= zone_num) {
				zone = true;
				cout << endl;
				cout << "you have choosen -->  ";
				arr_users[indexofuser].sub.zone = zone_var;
				arr_users[indexofuser].sub.zonePrice = arr_subscription[sub_type - 1].wallet_sub.zonesPrice[zone_var - 1];
				arr_users[indexofuser].sub.balancew -= arr_users[indexofuser].sub.zonePrice;
				cout << "Zone " << arr_users[indexofuser].sub.zone << ":" << "for" << arr_users[indexofuser].sub.zonePrice << "LE" << endl;
				cout << "your current balance :" << arr_users[indexofuser].sub.balancew << endl;
				break;
			}
		}
		else {
			cout << "Your choise is not available " << endl;
		}
	}
	finalize_subscription();
}

void renew_time(user_subscriptions sub) {
	//to get current date
	time_t now = time(NULL);
	tm localTime;
	localtime_s(&localTime, &now);
	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;
	localTime.tm_hour = 0;
	localTime.tm_min = 0;
	localTime.tm_sec = 0;
	now = mktime(&localTime);//setting time to midnight to compare dates

	cout << "Current date: " << day << "/" << month << "/" << year << endl;
	//to get expiry date
	string datestring = sub.expiry;
	tm expiryTime = {};
	stringstream ss(datestring);
	ss >> get_time(&expiryTime, "%d/%m/%Y");
	time_t expiry = mktime(&expiryTime);
	cout << "Expiry date: " << datestring << endl;
	//to get their differecnce 
	time_t final = expiry - now;
	final = final / (60 * 60 * 24);
	if (final == 0) { cout << "It's time to renew your subscription !" << endl; }
	else if (final < 0) { cout << "Your subscription has expired !" << endl; }
	else if (final == 1) { cout << "Renew is in 1 Day " << endl; }
	else if (final > 0) { cout << "Renew is in " << final << " Days " << endl; }
	int rew;
	int charge;
	cout << endl;
	do {
		cout << "1-Renew your subscription" << endl;
		cout << "2-Choose new subscription" << endl;
		cout << "3-Exit" << endl;

		rew = get_positive_integer();

		switch (rew) {
		case 1:
			if ((arr_users[indexofuser].balance - arr_users[indexofuser].sub.zonePrice) < 0) {
				cout << "No enough balance to renew, please recharge" << endl;
				cout << "1-Recharge now" << endl;
				cout << "2-Exit" << endl;
				charge = get_positive_integer();
				switch (charge) {
				case 1:
					recharge();
					break;
				case 2:
					break;
				}

			}
			else {
				arr_users[indexofuser].balance -= arr_users[indexofuser].sub.zonePrice;
				arr_users[indexofuser].sub.remaining_trips = arr_users[indexofuser].sub.Num_trips;
				finalize_subscription();
				cout << "Subscription Renewed" << endl;
				cout << "Your current balance : " << arr_users[indexofuser].balance << endl;
				cout << "Your remaining trips : " << arr_users[indexofuser].sub.remaining_trips << endl;
			}
			break;
		case 2:
			view_subsc_user();
			choose_again();
			break;
		case 3:
			cout << "Exiting" << endl;
			break;
		default:
			cout << "Invalid option please try again" << endl;
			break;
		}


	} while (rew != 3);

}

void view_subscription() {

	if (arr_users[indexofuser].sub.fixed == 'y') {
		cout << "Subscription Details for " << arr_users[indexofuser].username << endl;
		cout << "------------------------------------" << endl;
		cout << "Your current balance is : " << arr_users[indexofuser].balance << endl;
		cout << "Subscription Name : " << arr_users[indexofuser].sub.subscription_type << endl;
		cout << " Plan type : " << arr_users[indexofuser].sub.plan_type << endl;
		cout << "Activation Date : " << arr_users[indexofuser].sub.activation << endl;
		cout << "Expiry Date : " << arr_users[indexofuser].sub.expiry << endl;
		cout << "Remaining Trips : " << arr_users[indexofuser].sub.remaining_trips << endl;

	}
	else if (arr_users[indexofuser].sub.fixed == 'n') {
		cout << "Subscription Details for " << arr_users[indexofuser].username << endl;
		cout << "------------------------------------" << endl;
		cout << "Your current balance is : " << arr_users[indexofuser].balance << endl;
		cout << "Subscription Name : " << arr_users[indexofuser].sub.subscription_type << endl;
		cout << "Activation Date : " << arr_users[indexofuser].sub.activation << endl;
		cout << "There is no expiry Date for this subscription  " << endl;
		cout << "Your balance in the " << arr_users[indexofuser].sub.subscription_type << " plan is :" << arr_users[indexofuser].sub.balancew << endl;
	}

}

void setActivationDate() {

	time_t now = time(NULL);
	tm localTime;
	localtime_s(&localTime, &now);
	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;
	string activation = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	arr_users[indexofuser].sub.activation = activation;

}

void saveExpiry() {
	time_t now = time(NULL);
	tm localTime;
	localtime_s(&localTime, &now);

	if (arr_users[indexofuser].sub.fixed == 'y') {
		if (arr_users[indexofuser].sub.plan_type == "month") {
			localTime.tm_mon += arr_users[indexofuser].sub.duriation_plan_type;
		}
		else if (arr_users[indexofuser].sub.plan_type == "year") {
			localTime.tm_year += arr_users[indexofuser].sub.duriation_plan_type;
		}
		mktime(&localTime);
		int day = localTime.tm_mday;
		int month = localTime.tm_mon + 1;
		int year = localTime.tm_year + 1900;
		arr_users[indexofuser].sub.expiry = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
	else if (arr_users[indexofuser].sub.fixed == 'n') {
		arr_users[indexofuser].sub.expiry = "0";
		return;
	}



}


void save_user_subsc() {
	ofstream file("subsc.txt");
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < number_of_users_in_array; i++) {
		file << arr_users[i].sub.fixed << "   "
			<< arr_users[i].username << "   "
			<< arr_users[i].id << "   ";

		if (arr_users[i].sub.fixed == 'y') {
			file
				<< arr_users[i].sub.subscription_type << "   "
				<< arr_users[i].sub.plan_type << "   "
				<< arr_users[i].sub.duriation_plan_type << "   "
				<< arr_users[i].sub.Num_trips << "  "
				<< arr_users[i].sub.remaining_trips << "   "
				<< arr_users[i].sub.zone << "   "
				<< arr_users[i].sub.zonePrice << "   "
				<< arr_users[i].sub.activation << "   "
				<< arr_users[i].sub.expiry << endl;
		}
		if (arr_users[i].sub.fixed == 'n')
		{
			file << arr_users[i].sub.subscription_type << "   "
				<< arr_users[i].sub.zone << "   "
				<< arr_users[i].sub.zonePrice << "   "
				<< arr_users[i].sub.activation << "   "
				<< arr_users[i].sub.balancew << endl;
		}
	}

	file.close();
}

void load_user_subsc() {
	ifstream file("subsc.txt");
	if (!file) {
		cout << "No subscription data found!" << endl;
		return;
	}
	for (int i = 0;i < number_of_users_in_array;i++) {
		file >> arr_users[i].sub.fixed
			>> arr_users[i].username
			>> arr_users[i].id;

		if (arr_users[i].sub.fixed == 'y') {
			file
				>> arr_users[i].sub.subscription_type
				>> arr_users[i].sub.plan_type
				>> arr_users[i].sub.duriation_plan_type
				>> arr_users[i].sub.Num_trips
				>> arr_users[i].sub.remaining_trips
				>> arr_users[i].sub.zone
				>> arr_users[i].sub.zonePrice
				>> arr_users[i].sub.activation
				>> arr_users[i].sub.expiry;
		}
		if (arr_users[i].sub.fixed == 'n')
		{
			file >> arr_users[i].sub.subscription_type
				>> arr_users[i].sub.zone
				>> arr_users[i].sub.zonePrice
				>> arr_users[i].sub.activation
				>> arr_users[i].sub.balancew;
		}

	}

	file.close();
}

void update_subscription() {
	cout << "\n You must choose subscription before you start the journey \n" << endl;
	view_subsc_user();
	choose_again();
}

void choose_subscription() {

	charge_balance();
	cout << "\n You must choose subscription before you start the journey \n" << endl;
	view_subsc_user();
	user_choice();

}

void manage_plan() {
	long long choice;
	string ans;
	cout << "welcome! how do you want to manage your plan?" << endl;
	cout << "******************************************" << endl;
	ans = "y";
	while (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES" || ans == "Yes") {

		cout << "Choose an option from the following:" << endl << "1-View subscription"
			<< endl << "2-Renew subscription" << endl << "3-Upgrade subscription" << endl;
		cin >> choice;


		switch (choice) {
		case 1: view_subscription();break;
		case 2: renew_time(arr_users[indexofuser].sub);break;
		case 3: update_subscription(); break;
		default: cout << "Invalid option ! please choose from the presented options" << endl; continue;
		}
		cout << "Do you want to manage anything else in your plan? (Y/N)";cin >> ans;
	}
}

//-------------------------------- moaaz & omar part--------------------------------//

int HelloFunction()  /// the welcome function 
{
	string ans;  bool validinput = 0;

	cout << "\n\t\t\t\t\t Welcome to \"CAIRO RIDE PROGRAM\" !\n"

		<< " \t\t\t\t\t" << lineshapeforheader << "\n\n";  string choose;

	cout << lineshape << "\n\n";
	do
	{
		cout << "Please, Enter the choice you want to perform :- \n\n"
			<< "Press [ 1 ] to create a new account .\n\n"
			<< "Press [ 2 ] to Login to your account .\n\n"
			<< "Your choice ---> ";
		do
		{
			cin >> ans;
			if (ans != "1" && ans != "2")
			{
				cout << "Invalid input , please Enter a correct choice [ 1 ] <-OR-> [ 2 ]\n\n";
			}
			else
			{
				validinput = 1;
			}

		} while (validinput == 0);

		cout << "\nAre you sure you want to continue with this choice \? (y or Y)-->[ yes ]  <<--->>  (n or N)-->[no]";
		cin.ignore(1000, '\n');
		cin >> choose;

		while (choose != "n" && choose != "N" && choose != "y" && choose != "Y")
		{
			cout << "\nInvalid input , please Enter a valid input (y or Y)-->[ yes ]  <<--->>  (n or N)-->[no]: ";
			cin.ignore(1000, '\n');
			cin >> choose;
			cout << endl;
		}

	} while (choose == "n" || choose == "N");


	int answer = stoi(ans);

	cout << lineshape << endl << endl;

	return answer;
}

void ReadFromFile()  /// the function that fills the array from the file
{
	ifstream inputfromfile("data of users.txt");

	inputfromfile.ignore(1000, '\n');



	inputfromfile >> number_of_users_in_array;

	for (int i = 0;i < number_of_users_in_array;i++)
	{
		inputfromfile >> arr_users[i].username
			>> arr_users[i].id
			>> arr_users[i].admin_role
			>> arr_users[i].sub.fixed;
		if (arr_users[i].sub.fixed == 'y') {
			inputfromfile
				>> arr_users[i].sub.subscription_type
				>> arr_users[i].sub.expiry
				>> arr_users[i].sub.activation
				>> arr_users[i].sub.plan_type
				>> arr_users[i].sub.Num_trips
				>> arr_users[i].sub.duriation_plan_type
				>> arr_users[i].sub.remaining_trips
				>> arr_users[i].sub.zonePrice
				>> arr_users[i].sub.zone;
		}
		if (arr_users[i].sub.fixed == 'n') {
			inputfromfile
				>> arr_users[i].sub.subscription_type
				>> arr_users[i].sub.activation
				>> arr_users[i].sub.balancew;

		}
		inputfromfile
			>> arr_users[i].balance
			>> arr_users[i].pass
			>> arr_users[i].contactdet.email;
	}

	inputfromfile.close();

	ifstream inputcomplaint("complains.txt");  string temp;
	inputcomplaint.ignore(1000, '\n');
	for (int i = 0;i < number_of_users_in_array;i++)
	{
		inputcomplaint >> temp >> temp;

		getline(inputcomplaint, arr_users[i].complaints);

	}
	inputcomplaint.close();
}

bool SignInFun(bool& validpasskey)
{
	string username;

	char ch;  int trials = 3; bool IsFound = false;

	cout << "\t\t\t\t\t ----> LogIn .... \n\n";

	/// reading info (name - password )------------------------------------------------------

	while (trials--)
	{
		IsFound = false;  password.clear();

		cout << "Enter your username :- ";
		cin >> name;

		cout << endl;

		cout << "Enter your password :- ";



		while (1)  ///  this loop make the password invisible during writing -----------------------------
		{
			ch = _getch();

			if (ch == 8 && (!password.empty()))
			{
				cout << "\b \b";password.pop_back();
			}
			else if (ch == '\r')
			{
				if (!password.empty())
					break;

				else
				{
					cout << "\nEmpty password , please Enter the password :- ";
				}
			}
			else if (ch != 8)
			{
				cout << "*";   password.push_back(ch);
			}

		}

		/// test if his info are true or false---------------------------------------------------------------

		for (int i = 0;i < number_of_users_in_array;i++)
		{
			if (name == arr_users[i].username && password == arr_users[i].pass)
			{
				IsFound = 1; indexofuser = i;
				current_user_id = arr_users[i].id;

				break;
			}
		}

		if (!IsFound && trials != 0)
		{
			cout << " \n\n----> [ WRONG INFO ]  (The Username or Password is incorrect !!! ) , please try again .\n\n\n\n";
		}
		else if (IsFound)
		{
			if (arr_users[indexofuser].admin_role == 0)
			{
				cout << "\n\n YOU SIGNED IN SUCCESSFULLY !!! \n\n";
			}
			break;
		}
	}
	///----------------------------------------------------------------------------------------------------------

	if (!IsFound)  ///if the user enterd the info wrong in 3 trials
	{
		int trials_after_failing = 3;  string alternative_way;  bool validname = 0;

		cout << " \n\n\n----> You may forget the password enter the id instead . <--- \n\n\n";
		cout << " Enter your username :- "; cin >> name;

		while (validname == 0)
		{
			for (int i = 0;i < number_of_users_in_array;i++)
			{
				if (arr_users[i].username == name)
				{
					indexofuser = i; validname = 1; break;
				}
			}

			if (validname == 0)
			{
				cout << "\n Invalid name !!!\n\nplease Enter your actual name :- ";
				cin >> name;
			}

		}




		while (trials_after_failing--)
		{
			cout << "\n Enter the id :- ";
			cin >> alternative_way;

			if (alternative_way == arr_users[indexofuser].id)
			{
				if (arr_users[indexofuser].admin_role == 0)
				{
					cout << "\n\n YOU SINGNED IN SUCCESSFULLY !!!\n\n";
				}
				IsFound = 1;

				break;
			}
			else
			{
				cout << " The id is incorrect !!!\n";

				if (trials_after_failing == 0)
				{
					cout << endl << endl << " You don't have account in this program \n\n";
				}
			}

		}
	}
	if (!IsFound)
	{
		indexofuser = 0;
	}
	else if (IsFound)
	{
		const string passkey = "#ADMIN#2025"; int tries = 3; string trypasskey;

		if (arr_users[indexofuser].admin_role)
		{
			cout << "\n\nThis email is an admin email, to continue as admin enter the verify passkey !!!";

			while (tries--)
			{
				cout << "\n\nThe passkey---> ";
				cin >> trypasskey;
				if (trypasskey == passkey)
				{
					cout << "\nYou logged in as an admin successfully \n\n";

					validpasskey = 1;
					break;
				}
				else if (trypasskey != passkey && tries != 0)
				{
					cout << "The passkey is incorrect ,try again ";
				}
			}

			if (!validpasskey)
			{
				cout << "The passkey isn't true!!! you failed to login as an admin. please review the passkey and try again \n\n";
			}
		}
	}
	cout << "\n\n" << lineshape << endl << endl;

	return IsFound;
}

bool  newaccount()
{

	cout << "\n\t\t\t\t\t \" Welcome To New Account Page \""
		<< "\n\t\t\t\t\t " << ustars;  cin.ignore();

	///------------------------------------------------------------------------------///
	bool username_exist;
	do {
		username_exist = false;

		cout << endl << "\n Enter Username : ";
		getline(cin, newacc.username);
		while (newacc.username.empty())
		{
			cout << " \nInvalid input !!! \n Enter the username correctly :";
			getline(cin, newacc.username);
		}
		for (int k = 0;k < usersnum;k++)
		{

			if (newacc.username == arr_users[k].username)
			{
				cout << " \nthis name exists already !! use another .";
				username_exist = true;
			}

		}
	} while (username_exist);
	///------------------------------------------------------------------------------///

	bool pass_exist;
	do {
		pass_exist = false;
		cout << "\n Enter password ( 8 characters or more) : ";
		getline(cin, newacc.pass);
		while (newacc.pass.empty() || newacc.pass.size() < 8)
		{
			cout << " \nInvalid input !!! \n Enter the password correctly :";
			getline(cin, newacc.pass);
		}
		for (int k = 0;k < usersnum;k++)
		{

			if (newacc.pass == arr_users[k].pass)
			{
				cout << " \nthis pass exists already !! use another ." << endl;
				pass_exist = true;
			}

		}
	} while (pass_exist);

	///------------------------------------------------------------------------------///




	bool email_exist, invalid_email;
	do {

		do
		{
			invalid_email = true;

			cout << "\n Enter E_Mail (it must have name followed by \"@gmail.com\"): ";
			char ch;

			while (cin.get(ch) && ch != '\n') //if there is input and isn't enter
			{
				newacc.contactdet.email.push_back(ch);

			}
			if (newacc.contactdet.email.size() > 10)
			{
				string check = newacc.contactdet.email.substr(newacc.contactdet.email.size() - 10, 10);
				if (check == "@gmail.com")
				{
					invalid_email = false;
				}
			}
			if (invalid_email || newacc.contactdet.email.size() < 11)
			{
				cout << " \n Incorrect e_mail !! \n ";
				newacc.contactdet.email.clear();
			}



		} while (invalid_email || newacc.contactdet.email.empty());///-->if it @gmail.com without name


		email_exist = false;

		for (int i = 0; i < usersnum;i++)
		{
			if (arr_users[i].contactdet.email == newacc.contactdet.email)
			{
				email_exist = true;
				cout << " \nthis e_mail exists already !!! use another .\n";
				newacc.contactdet.email.clear();
				break;
			}
		}

	} while (email_exist);



	choose_subscription();
	///------------------------------------------------------------------------------///

	srand(time(NULL));	///---> to generate dif num each time  
	if (newacc.sub.subscription_type.empty())
	{
		newacc.sub.subscription_type = '0';
	}

	newacc.id = to_string(rand() % 10000);
	for (int i = 0;i < number_of_users_in_array;i++)
	{
		if (newacc.id == arr_users[i].id)
		{

			newacc.id = to_string(rand() % 10000);
			i = 0;
		}
	}

	///------------------------------------------------------------------------------///

	arr_users[number_of_users_in_array] = newacc;

	number_of_users_in_array++;


	cout << "\n\t\t\t\t\t \" You added new account seccessfuly \""
		<< "\n\n " << lineshape << endl << endl;
	system("pause");
	return true;
}

void saveusersinfo()  /// this function saves complains & all info in user struct
{
	ofstream outfile_complaints("complains.txt", ios::out);

	outfile_complaints << "The sequence of data is (name---> id ----> complaints)\n\n";

	for (int i = 0;i < number_of_users_in_array;i++)
	{
		outfile_complaints << arr_users[i].username << "  " << arr_users[i].id;

		if (arr_users[i].complaints != "  NO COMPLAINS")
		{
			outfile_complaints << " ";
		}

		if (arr_users[i].complaints != "")
		{
			outfile_complaints << arr_users[i].complaints << endl;
		}
		else if (arr_users[i].complaints == "")
		{
			outfile_complaints << "  NO COMPLAINS" << endl;
		}
	}

	ofstream dataofusers("data of users.txt", ios::out);

	dataofusers << "information of person is in this sequence :(name--> id  --> role --> subsucribtion [   fixed - subscription_type  -  expiry  -  activation  -  plan_type  -  Num_trips  -  duriation_plan type  -  remaining_trips  -  balance wallet  -  zoneprice  -  zone  -  wallet name  ] ------> balance --> password-->email)\n";
	dataofusers << number_of_users_in_array << endl << endl;


	for (int i = 0;i < number_of_users_in_array;i++)
	{
		dataofusers << arr_users[i].username << "   "
			<< arr_users[i].id << "   "
			<< arr_users[i].admin_role << "   "
			<< arr_users[i].sub.fixed << "   ";
		if (arr_users[i].sub.fixed == 'y') {
			dataofusers
				<< arr_users[i].sub.subscription_type << " "
				<< arr_users[i].sub.expiry << " "
				<< arr_users[i].sub.activation << " "
				<< arr_users[i].sub.plan_type << " "
				<< arr_users[i].sub.Num_trips << " "
				<< arr_users[i].sub.duriation_plan_type << " "
				<< arr_users[i].sub.remaining_trips << " "
				<< arr_users[i].sub.zonePrice << " "
				<< arr_users[i].sub.zone << "   ";
		}
		if (arr_users[i].sub.fixed == 'n') {
			dataofusers
				<< arr_users[i].sub.subscription_type << " "
				<< arr_users[i].sub.activation << " "
				<< arr_users[i].sub.balancew << "   ";

		}
		dataofusers
			<< arr_users[i].balance << "   "
			<< arr_users[i].pass << "   "
			<< arr_users[i].contactdet.email << endl;
	}

	dataofusers.close();
}

//______________________________aly & mohamed part______________________________//
void metro_lines();

float calculated_fare(int zone) {
	float fare = 0;
	fare = arr_users[indexofuser].sub.remaining_trips - 1;
	arr_users[indexofuser].sub.remaining_trips -= 1;
	cout << "\n your current trips is :" << fare << endl;

	return fare;
}

void save_rides_to_file() {
	ofstream file("history rides.txt");
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}
	for (int i = 0; i < ride_cnt; i++) {
		file << rides[i].id << "     "
			<< rides[i].entryStation << "     "
			<< rides[i].ExitStation << "     "
			<< rides[i].RideFare << "     "
			<< rides[i].Date << endl;
	}
	file.close();
}

void loadRideHist() {
	ifstream file("history rides.txt");
	if (!file) {
		cout << "No ride history found yet.\n";
		return;
	}

	while (file >> rides[ride_cnt].id
		>> rides[ride_cnt].entryStation
		>> rides[ride_cnt].ExitStation
		>> rides[ride_cnt].RideFare
		>> rides[ride_cnt].Date) {
		ride_cnt++;
	}
}//all function is incorrect

void DisplayHistoryRidesToADMIN() {
	cout << "\n--- Ride History for ADMIN name : " << arr_users[indexofuser].username << " ---\n";
	bool found = false;
	int i = 0;

	while (rides[i].entryStation != "") {
		cout << endl;
		cout << "Trip number " << i + 1 << endl;
		cout << "User ID :" << rides[i].id << " || ";
		cout << "Entry: " << rides[i].entryStation << " || "
			<< " Exit: " << rides[i].ExitStation << " || "
			<< " Fare: " << rides[i].RideFare
			<< " || Date: " << rides[i].Date << endl;
		cout << "____________________________________________________________";
		found = true;

		i++;

	}


	if (!found)
		cout << "No rides found.\n";
	system("pause");
}

void DisplayHistoryRides() {
	cout << "\n--- Ride History for User ID: " << arr_users[indexofuser].id << " ---\n";
	bool found = false;
	int cntride = 1;
	for (int i = 0; i < MAX_rides; i++) {
		if (arr_users[indexofuser].sub.fixed == 'n') {
			if (rides[i].id == arr_users[indexofuser].id) {
				cout << "Trip number " << cntride << endl;
				cout << " Entry station : " << rides[i].entryStation << endl
					<< " Exit station : " << rides[i].ExitStation << endl
					<< " Your subscription is : " << arr_users[indexofuser].sub.subscription_type << endl
					<< " And you take : " << rides[i].RideFare << endl
					<< " From Your balance \n"
					<< " Your remaining balance is : " << arr_users[indexofuser].sub.balancew << endl
					<< "  Date of trip : " << rides[i].Date << endl;
				cout << "____________________________________________________________" << endl;

				found = true;
				cntride++;
			}
		}
		if (arr_users[indexofuser].sub.fixed == 'y') {
			if (rides[i].id == arr_users[indexofuser].id) {
				cout << "Trip number " << cntride << endl;
				cout << "Entry station: " << rides[i].entryStation << endl
					<< " Exit station : " << rides[i].ExitStation << endl
					<< "Your subscription is : " << arr_users[indexofuser].sub.subscription_type << endl
					<< "And you used one trip from your travel balance and your remaining trips is :"
					<< rides[i].RideFare << endl
					<< " Date of the trip : " << rides[i].Date << endl;
				cout << "____________________________________________________________" << endl;
				found = true;
				cntride++;
			}
		}

	}
	if (!found)
		cout << "No rides found.\n";
}

void admin_rides() {
	cout << "\n for add or delete stations enter : 1\n"
		<< "\n for see all the ride history for all user press : 2\n";
	int adminride;
	cout << "\nyour choice is -->  ";
	cin >> adminride;
	switch (adminride)
	{
	case 1:metro_lines();break;

	case 2: DisplayHistoryRidesToADMIN();break;

	default:cout << "please enter from the choices ";break;
	}



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

void stations2file() {
	ofstream output("stations.txt", ios::out);
	if (!output.is_open()) {
		cout << "Error: Could not open stations.txt for writing\n";
		return;
	}

	output << "line 1" << "  \t\t\t\tline 2" << "  \t\t\t\t\tline 3" << endl << endl;

	for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
		for (int j = 0; j < NUM_LINES; j++) {
			output << left << setw(20) << allStations[i][j].name << "\t";
		}
		output << endl;
	}

	output.close();
}

void buildGraph() {
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			graph[i][j] = -1;

	for (int j = 0; j < NUM_LINES; j++) {
		for (int i = 0; i < MAX_STATIONS_PER_LINE - 1; i++) {
			if (allStations[i][j].name != "-" && allStations[i + 1][j].name != "_") {
				int from = allStations[i][j].number;
				int to = allStations[i + 1][j].number;
				graph[from][to] = j + 1;
				graph[to][from] = j + 1;
			}
		}
	}
	//this is the constant stations 
	graph[19][50] = 2; graph[50][19] = 1;
	graph[52][99] = 3; graph[99][52] = 2;
	graph[20][100] = 3; graph[100][20] = 1;
	graph[46][115] = 3;graph[115][46] = 2;

}

bool bfs(int start, int end, int parent[]) {
	bool visited[MAX] = { false };
	int queue[MAX], front = 0, rear = 0;

	queue[rear++] = start;
	visited[start] = true;
	parent[start] = -1;

	while (front < rear) {
		int current = queue[front++];
		if (current == end) return true;

		for (int i = 1; i <= num_stations; i++) {
			if (graph[current][i] != -1 && !visited[i]) {
				visited[i] = true;
				parent[i] = current;
				queue[rear++] = i;
			}
		}
	}
	return false;
}

void calc_kit_kat_index()
{
	for (int i = 0;i < MAX_STATIONS_PER_LINE;i++)
	{
		if (allStations[i][2].name == "Kit_Kat.")
		{
			kit_kat_index = allStations[i][2].number;
			break;
		}

	}
	for (int i = 0;i < 20;i++)
	{
		if (allStations[(kit_kat_index - (2 * MAX_STATIONS_PER_LINE)) + i][2].name == "Switching.")
		{
			switching_index = allStations[(kit_kat_index - (2 * MAX_STATIONS_PER_LINE)) + i][2].number;
			break;
		}
	}
}

void findShortestPath(int start, int end) {
	int parent[MAX];
	calc_kit_kat_index();
	if ((start > kit_kat_index && start < switching_index && end > switching_index) ||
		(end > kit_kat_index && end<switching_index && start>switching_index))
	{
		cout << "\n--- Route ---\n";
		if (start < switching_index)     ///start in rod elfarag branch
		{
			int cnt = start - kit_kat_index;
			for (int i = cnt - 1;i >= -1;i--)
			{
				stationcnt++;
				cout << "-> " << allStations[kit_kat_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name << endl;
			}

			for (int i = 0;i < (end - switching_index);i++)
			{
				stationcnt++;
				cout << "-> " << allStations[i + switching_index - (2 * MAX_STATIONS_PER_LINE)][2].name << endl;
			}

		}
		else if (start > switching_index)        ///start in cairo uni branch
		{
			int cnt = start - switching_index;
			for (int i = cnt - 1;i >= 0;i--)
			{
				stationcnt++;
				cout << "-> " << allStations[switching_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name << endl;
			}
			for (int i = -1;i < (end - kit_kat_index);i++)
			{
				stationcnt++;
				cout << "-> " << allStations[kit_kat_index + i - (2 * MAX_STATIONS_PER_LINE)][2].name << endl;
			}

		}
		return;
	}
	if (!bfs(start, end, parent)) {
		cout << "No path found.\n";
		return;
	}

	int path[MAX], count = 0;
	for (int at = end; at != -1; at = parent[at])
		path[count++] = at;

	cout << "\n--- Route ---\n";

	int lastLine = -1;
	string lastName = "";

	for (int i = count - 1; i > 0; i--) {
		int curr = path[i];
		int next = path[i - 1];

		string currName = allStations[(curr - 1) % MAX_STATIONS_PER_LINE][(curr - 1) / MAX_STATIONS_PER_LINE].name;
		string nextName = allStations[(next - 1) % MAX_STATIONS_PER_LINE][(next - 1) / MAX_STATIONS_PER_LINE].name;

		if (currName == nextName) continue;

		int line = graph[curr][next];

		if (line != lastLine && lastLine != -1) {
			cout << "-- Switch to Line " << line << " --\n";
		}

		cout << "-> " << currName << "\n";
		lastLine = line;
		lastName = currName;
	}


	string lastStationName = allStations[(end - 1) % MAX_STATIONS_PER_LINE][(end - 1) / MAX_STATIONS_PER_LINE].name;
	if (lastStationName != lastName) {
		cout << "-> " << lastStationName << "\n";
	}
}

void checkforzones(int start, int end) {
	int parent[MAX];
	stationcnt = 0;
	calc_kit_kat_index();

	if ((start > kit_kat_index && start < switching_index && end > switching_index) ||
		(end > kit_kat_index && end<switching_index && start>switching_index))
	{
		if (start < switching_index)     ///start in rod elfarag branch
		{
			int cnt = start - kit_kat_index;
			for (int i = cnt - 1;i >= -1;i--)
			{
				stationcnt++;
				allStations[kit_kat_index + i - 80][2].name;
			}

			for (int i = 0;i < (end - switching_index);i++)
			{
				stationcnt++;
				allStations[i + switching_index - 80][2].name;
			}

		}
		else if (start > switching_index)        ///start in cairo uni branch
		{
			int cnt = start - switching_index;
			for (int i = cnt - 1;i >= 0;i--)
			{
				stationcnt++;
				allStations[switching_index + i - 80][2].name;
			}
			for (int i = -1;i < (end - kit_kat_index);i++)
			{
				stationcnt++;
				allStations[kit_kat_index + i - 80][2].name;
			}

		}
		return;
	}
	if (!bfs(start, end, parent)) {

		return;
	}

	int path[MAX], count = 0;
	for (int at = end; at != -1; at = parent[at])
		path[count++] = at;



	int lastLine = -1;
	string lastName = "";

	for (int i = count - 1; i > 0; i--) {
		int curr = path[i];
		int next = path[i - 1];
		stationcnt++;
		string currName = allStations[(curr - 1) % MAX_STATIONS_PER_LINE][(curr - 1) / MAX_STATIONS_PER_LINE].name;
		string nextName = allStations[(next - 1) % MAX_STATIONS_PER_LINE][(next - 1) / MAX_STATIONS_PER_LINE].name;

		if (currName == nextName) continue;

		int line = graph[curr][next];

		if (line != lastLine && lastLine != -1) {
			line;
		}

		currName;
		lastLine = line;
		lastName = currName;
	}


	string lastStationName = allStations[(end - 1) % MAX_STATIONS_PER_LINE][(end - 1) / MAX_STATIONS_PER_LINE].name;
	if (lastStationName != lastName) {
		lastStationName;
	}
}

void shiftStationsDown(int line, int index) {
	for (int i = MAX_STATIONS_PER_LINE - 2; i >= index; --i) {
		allStations[i + 1][line] = allStations[i][line];
		if (allStations[i + 1][line].name != "-" && allStations[i + 1][line].name != "_") {
			allStations[i + 1][line].number += 1;
		}
	}
	allStations[index][line].name = "-";
}

void shiftStationsUp(int line, int index) {
	for (int i = index; i < MAX_STATIONS_PER_LINE - 1; ++i) {
		allStations[i][line] = allStations[i + 1][line];
		if (allStations[i][line].name != "-" && allStations[i][line].name != "_") {
			allStations[i][line].number -= 1;
		}
	}
	allStations[MAX_STATIONS_PER_LINE - 1][line].name = "-";
}

bool isInterchangeStation(const string& name) {
	return name == "Sadat" || name == "Al_Shohadaa" || name == "Attaba" || name == "Kit_Kat" || name == "Cairo_University";
}

void printStations(Station allStations[MAX_STATIONS_PER_LINE][NUM_LINES]) {
	//  Count valid stations per line
	int counts[NUM_LINES] = { 0 };
	for (int j = 0; j < NUM_LINES; j++) {
		for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
			const auto& st = allStations[i][j];
			if (st.name != "-" && st.name != "_" && st.name != "Switching.") {
				counts[j]++;
			}
		}
	}

	//  Find the maximum number of rows needed
	int maxRows = 0;
	for (int j = 0; j < NUM_LINES; j++) {
		maxRows = max(maxRows, counts[j]);
	}

	//  Choose a column width that fits your longest " StationName"
	const int colWidth = 30;

	//  Print outlines
	cout << "\nAvailable stations:\n\n";
	for (int j = 0; j < NUM_LINES; j++) {
		cout << left << setw(colWidth)
			<< ("Line " + to_string(j + 1));
	}
	cout << "\n";
	for (int j = 0; j < NUM_LINES; j++) {
		string header = "Line " + to_string(j + 1);
		cout << left << setw(colWidth)
			<< string(header.size(), '-');
	}
	cout << "\n";

	//  Print each row of stations
	for (int row = 0; row < maxRows; row++) {
		for (int j = 0; j < NUM_LINES; j++) {
			int cntr = 0;//to know what valid station i counterd 
			string entry;
			for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {//use const to ensure that i dont change the station for safety
				const auto& station_var = allStations[i][j];//to not go error with stack overflow so i do it refrence & auto to copy the same data type of the right var 
				if (station_var.name != "-" && station_var.name != "_" && station_var.name != "Switching.") {
					if (cntr == row) {
						entry = to_string(station_var.number) + ". " + station_var.name;
						break;
					}
					cntr++;
				}
			}
			cout << left << setw(colWidth)
				<< (entry.empty() ? "" : entry);
		}
		cout << "\n";
	}
}

void metro_lines() {
	buildGraph();

	if (realadmin_by_keypass) {
		int choice;

		do {
			cout << "\nAdmin Panel:\n";
			cout << "\n1. Add Station\n\n2. Delete Station\n\n3. Save Changes\n\n4. Exit Admin Mode\n\n";
			cout << "\nEnter choice: ";
			cin >> choice;


			if (choice == 1) {
				int line, index;
				cout << "Enter line number (1-3): ";
				cin >> line;
				cout << "Enter station index (0-39): ";
				cin >> index;

				if (line < 1 || line > 3 || index < 0 || index >= MAX_STATIONS_PER_LINE) {
					cout << "Invalid input.\n";
					continue;
				}



				shiftStationsDown(line - 1, index);

				cout << "Enter station name: ";
				cin.ignore();
				getline(cin, allStations[index][line - 1].name);

				allStations[index][line - 1].number = (line - 1) * MAX_STATIONS_PER_LINE + (index + 1);
				allStations[index][line - 1].line = line;
				num_stations++;
				buildGraph();
				cout << "Station added.\n";
			}

			else if (choice == 2) {
				int line, index;
				cout << "Enter line number (1-3): ";
				cin >> line;
				cout << "Enter station index (1-40): ";
				cin >> index;
				index -= 1;

				if (line < 1 || line > 3 || index < 0 || index >= MAX_STATIONS_PER_LINE) {
					cout << "Invalid input.\n";
					continue;
				}

				if (allStations[index][line - 1].name == "-") {
					cout << "Station does not exist.\n";
					continue;
				}

				if (isInterchangeStation(allStations[index][line - 1].name)) {
					cout << "You cannot delete an interchange station.\n";
					continue;
				}

				shiftStationsUp(line - 1, index);
				num_stations--;
				buildGraph();
				cout << "Station deleted.\n";
			}
			else if (choice == 3) {

				cout << "Changes saved.\n";
			}
		} while (choice != 4);
	}
	else {

		char again = '\0';
		while (true) {
			/*cout << "\nAvailable stations:\n";
			for (int j = 0; j < NUM_LINES; j++) {
				cout << "Line " << j + 1 << ":\n";
				for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
					if (allStations[i][j].name != "-" && allStations[i][j].name != "_") {
						cout << allStations[i][j].number << ". " << allStations[i][j].name << "\n";
					}
				}
			}*/

			printStations(allStations);

			int start, end;
			cout << "\nEnter start station number: ";
			cin >> start;
			cout << "Enter end station number: ";
			cin >> end;

			if (start < 1 || start > num_stations || end < 1 || end > num_stations || start == end) {
				cout << "Invalid input.\n";
			}
			else {
				checkforzones(start, end);

				if (stationcnt >= 1 && stationcnt <= 9)
					real_zone = 1;

				if (stationcnt >= 10 && stationcnt <= 16)
					real_zone = 2;

				if (stationcnt >= 17 && stationcnt <= 23)
					real_zone = 3;

				if (stationcnt >= 24)
					real_zone = 4;



				if (arr_users[indexofuser].sub.fixed == 'n') {
					for (int i = 0;i < num_of_subsc;i++) {

						if (arr_users[indexofuser].sub.subscription_type == arr_subscription[i].plan_name)
						{
							if (arr_users[indexofuser].sub.balancew >= arr_subscription[i].wallet_sub.zonesPrice[real_zone - 1])
							{
								findShortestPath(start, end);
								rides[ride_cnt].entryStation = allStations[(start - 1) % MAX_STATIONS_PER_LINE][(start - 1) / MAX_STATIONS_PER_LINE].name;
								rides[ride_cnt].ExitStation = allStations[(end - 1) % MAX_STATIONS_PER_LINE][(end - 1) / MAX_STATIONS_PER_LINE].name;
								rides[ride_cnt].RideFare = not_fixed(stationcnt);
								rides[ride_cnt].Date = getCurrentDate();
								rides[ride_cnt].id = arr_users[indexofuser].id;
								ride_cnt++;

							}
							else {
								int ans;
								cout << "Your wallet balance is low please charge it " << endl
									<< "\n To renew press : 1\n"
									<< "\n to choose another station press : 2\n";
								cin >> ans;
								if (ans == 1) {
									renew_time(arr_users[indexofuser].sub);
								}
								else if (ans == 2) {
									break;
								}

							}
						}

					}


				}
				if (arr_users[indexofuser].sub.fixed == 'y') {


					bool not_your_zone = true;
					if (real_zone <= arr_users[indexofuser].sub.zone) {
						not_your_zone = false;
						if (arr_users[indexofuser].sub.remaining_trips > 0) {
							findShortestPath(start, end);
							rides[ride_cnt].entryStation = allStations[(start - 1) % MAX_STATIONS_PER_LINE][(start - 1) / MAX_STATIONS_PER_LINE].name;
							rides[ride_cnt].ExitStation = allStations[(end - 1) % MAX_STATIONS_PER_LINE][(end - 1) / MAX_STATIONS_PER_LINE].name;
							rides[ride_cnt].RideFare = calculated_fare(real_zone);
							rides[ride_cnt].Date = getCurrentDate();
							rides[ride_cnt].id = arr_users[indexofuser].id;
							ride_cnt++;
						}
						else {
							int ans;
							cout << "\n you have reached the maximum number of trips please recharge your subscription \n"
								<< "\n if you want to renew your subscription press : 1 \n"
								<< "\n if you want the main menu press : 2\n "
								<< "\n your choice is --> ";
							cin >> ans;
							if (ans == 1) {
								renew_time(arr_users[indexofuser].sub);
							}
							else if (ans == 2) {
								break;
							}
						}
					}
					if (not_your_zone) {
						cout << "\n you didnt subscripted to this zone please try another one \n";
						continue;
					}


				}
			}
			cout << "Do you want another trip? (Y/N): ";
			cin >> again;
			if (!(again == 'y' || again == 'Y' || again == 'yes' || again == 'YES')) {
				break;
			}
		}

	}


}

//-----------------------------------Maher part -----------------------------------//

bool isValidPassword(const string& pass) {
	if (pass.length() < 8) {
		cout << "Password must be at least 8 characters long!" << endl;
		return false;
	}

	return true;
}

bool isValidChoiceInput(const string& input) {
	for (char c : input) {
		if (!isdigit(c)) return false;
	}
	return true;
}

void Edit() {
	string response;  bool want_toComplain = 0;
	cout << "\nWelcome " << arr_users[indexofuser].username << endl;
	cout << lineshape << endl;
	cout << "Your current data is:\n" << endl;
	cout << "ID           : " << arr_users[indexofuser].id << endl;
	cout << "Password     : " << arr_users[indexofuser].pass << endl;
	cout << "Email        : " << arr_users[indexofuser].contactdet.email << endl;
	if (!arr_users[indexofuser].admin_role) {
		cout << "Balance      : " << arr_users[indexofuser].balance << endl;
	}
	cout << lineshape << endl;
	cout << "\nDo you want to change any information? (YES/NO): ";
	cin >> response;
	for (char& c : response) c = tolower(c);
	while (!(response == "yes" || response == "no")) {
		cout << "Invalid input, please enter again (YES/NO): ";
		cin >> response;
		for (char& c : response) c = tolower(c);
	}
	if (response == "yes") {
		do {
			int choice;
			bool valid_choice = false;
			while (!valid_choice) {
				string input;
				cout << "\nWhat would you like to edit?" << endl;
				cout << lineshape << endl;
				cout << "1. Edit Name" << endl;
				cout << "2. Edit Password" << endl;
				cout << "3. Edit Email" << endl;
				cout << "4. Submit Complaint" << endl;
				cout << "\nEnter your choice (1, 2, 3, 4): ";
				cin >> input;
				if (isValidChoiceInput(input)) {
					choice = stoi(input);
					switch (choice) {
					case 1: {
						string new_name;
						bool taken;
						do {
							taken = false;
							cout << "\nEnter your new name: ";
							cin >> new_name;
							for (int i = 0; i < 1000; i++) {
								if (i != indexofuser && arr_users[i].username == new_name) {
									taken = true;
									cout << "This name is already taken. Try another one.\n";
									break;
								}
							}
						} while (taken);
						arr_users[indexofuser].username = new_name;
						valid_choice = true;
						break;
					}
					case 2: {
						string new_pass;
						bool taken;
						do {
							taken = false;
							cout << "\nEnter your new password (at least 8 characters): ";
							cin >> new_pass;
							if (new_pass.length() < 8) {
								cout << "Password too short. Try again.\n";
								taken = true;
								continue;
							}
							for (int i = 0; i < 1000; i++) {
								if (i != indexofuser && arr_users[i].pass == new_pass) {
									taken = true;
									cout << "This password is already used. Try another one.\n";
									break;
								}
							}
						} while (taken);
						arr_users[indexofuser].pass = new_pass;
						valid_choice = true;
						break;
					}
					case 3: {
						string new_email;
						bool taken;
						do {
							taken = false;
							cout << "\nEnter your new email: ";
							cin >> new_email;
							for (int i = 0; i < 1000; i++) {
								if (i != indexofuser && arr_users[i].contactdet.email == new_email) {
									taken = true;
									cout << "This email is already used. Try another one.\n";
									break;
								}
							}
						} while (taken);
						arr_users[indexofuser].contactdet.email = new_email;
						valid_choice = true;
						break;
					}
					case 4: {
						want_toComplain = 1;   cin.ignore(1000, '\n');  string complain;

						cout << "\nEnter your complaint: ";

						getline(cin, complain);

						if (arr_users[indexofuser].complaints == "  NO COMPLAINS")
						{
							arr_users[indexofuser].complaints.clear();
						}

						arr_users[indexofuser].complaints += complain + " -- ";

						cout << "\nThank you! The admin will get back to you as soon as possible.\n";
						valid_choice = true;
						break;
					}
					}
				}
				else {
					cout << "Invalid input! Please enter a number between 1 and 4." << endl;
				}
			}
			cout << "\nDo you want to edit another piece of information? (YES/NO): ";
			cin >> response;
			for (char& c : response) c = tolower(c);
			while (!(response == "yes" || response == "no")) {
				cout << "Invalid input, please enter again (YES/NO): ";
				cin >> response;
				for (char& c : response) c = tolower(c);
			}
		} while (response == "yes");

		cout << "\nYour updated data is:\n";
		cout << lineshape << endl;
		cout << "Name         : " << arr_users[indexofuser].username << endl;
		cout << "ID           : " << arr_users[indexofuser].id << endl;
		cout << "Password     : " << arr_users[indexofuser].pass << endl;
		cout << "Email        : " << arr_users[indexofuser].contactdet.email << endl;
		if (!arr_users[indexofuser].admin_role) {
			cout << "Balance      : " << arr_users[indexofuser].balance << endl;
		}
		cout << lineshape << endl;
	}
	else {
		cout << "\nYour data is not updated." << endl;
	}
}

///////////////////////////////////////////////////////////////////////////////////

//all admin can do in the user //
void view_users_toAdmin()
{
	string line(25, '_');
	cout << "\nThe information of users :- \n" << line << endl << endl;

	for (int i = 0;i < number_of_users_in_array;i++)
	{
		if (arr_users[i].admin_role == 0)
		{
			if (arr_users[i].sub.fixed == 'y')
			{
				cout << "User #" << i - 1 << endl;

				cout << "NAME :- " << arr_users[i].username << endl;

				cout << "BALANCE :- " << arr_users[i].balance << endl;

				cout << "EMAIL :- " << arr_users[i].contactdet.email << endl;

				cout << "ID :- " << arr_users[i].id << endl;

				cout << "PASSWORD :- " << arr_users[i].pass << endl << endl;

				cout << "---> SUBSCRIPTION \n" << endl;

				cout << "subscription type :- " << arr_users[i].sub.subscription_type << endl;

				cout << "plan type :- " << arr_users[i].sub.plan_type << endl;

				cout << "fixed :- " << arr_users[i].sub.fixed << "\n";

				cout << "duration plan type :- " << arr_users[i].sub.duriation_plan_type << endl;

				cout << "number of trips :- " << arr_users[i].sub.Num_trips << endl;

				cout << "zone :- " << arr_users[i].sub.zone << "\n";

				cout << "zone price :- " << arr_users[i].sub.zonePrice << "\n";

				cout << "activation date :- " << arr_users[i].sub.activation << endl;

				cout << "expiry date :- " << arr_users[i].sub.expiry << endl;

				cout << "remaining trips :- " << arr_users[i].sub.remaining_trips << endl;

				cout << "COMPLAINS:-\n" << arr_users[i].complaints << endl;

				cout << lineshapeforheader << endl << endl;

			}
			if (arr_users[i].sub.fixed == 'n') {
				cout << "User #" << i - 1 << endl;

				cout << "NAME :- " << arr_users[i].username << endl;

				cout << "BALANCE :- " << arr_users[i].balance << endl;

				cout << "EMAIL :- " << arr_users[i].contactdet.email << endl;

				cout << "ID :- " << arr_users[i].id << endl;

				cout << "PASSWORD :- " << arr_users[i].pass << endl << endl;

				cout << "---> SUBSCRIPTION \n" << endl;

				cout << "subscription type :- " << arr_users[i].sub.subscription_type << endl;

				cout << "wallet name :- " << arr_users[i].sub.wallet_name << "\n";

				cout << "fixed :- " << arr_users[i].sub.fixed << "\n";

				cout << "zone :- " << arr_users[i].sub.zone << "\n";

				cout << "zone price :- " << arr_users[i].sub.zonePrice << "\n";

				cout << "activation date :- " << arr_users[i].sub.activation << endl;

				cout << "balance wallet :- " << arr_users[i].sub.balancew << endl;

				cout << "COMPLAINS:-\n" << arr_users[i].complaints << endl;

				cout << lineshapeforheader << endl << endl;
			}
		}
	}
}

void admin_change_user_subsc() {
	int user;
	int ans;
	bool finished = false;
	view_users_toAdmin();
	int numuser = number_of_users_in_array - 2;
	do {
		cout << "\nWhich user do you want to edit his subscription " << endl;
		cout << "\nYour choice is ";
		cin >> ans;
		if (ans >= numuser) {
			cout << "\nThis user is not available please enter another number " << endl;
		}
	} while (ans > numuser);
	int subscans;
	while (true) {
		bool month = false;
		bool year = false;
		int planvar;
		user = ans + 2;
		system("cls");
		cout << "\nThe user that you select is --> " << arr_users[user - 1].username << endl;
		cout << "\nwhat do you want to change in user subscription data \n";
		cout << "\nfor change the subscription type press : 1 \n"
			<< "\nfor charge balance press : 2 \n";
		cout << "\n Your choice is : ";
		cin >> subscans;
		cin.ignore();
		if (subscans == 1) {
			int sub_type;
			cout << "this is the available subscriptions please choose one \n";
			view(num_of_subsc);
			cout << "\n your choice is --> ";
			cin >> sub_type;
			cin.ignore();
			cout << "\n you choosed this subscription : ";
			cout << arr_subscription[sub_type - 1].plan_name;

			arr_users[user - 1].sub.subscription_type = arr_subscription[sub_type - 1].plan_name; //update user subsc type
			if (arr_subscription[sub_type - 1].fixed == 'y') {
				while (true) {
					arr_users[user - 1].sub.fixed = 'y';
					cout << "\nChoose your plan \n";
					cout << "\nyour choice is --> ";

					cin >> planvar;
					cin.ignore();
					if (planvar <= (arr_subscription[sub_type - 1].month_count))
					{
						arr_users[user - 1].sub.plan_type = "month";
						arr_users[user - 1].sub.duriation_plan_type = arr_subscription[sub_type - 1].month_sub[planvar - 1].duration;
						arr_users[user - 1].sub.Num_trips = arr_subscription[sub_type - 1].month_sub[planvar - 1].no_of_trips;
						arr_users[user - 1].sub.remaining_trips = arr_users[user - 1].sub.Num_trips;
						month = true;

						break;
					}
					else if ((planvar > (arr_subscription[sub_type - 1].month_count)) && (planvar <= ((arr_subscription[sub_type - 1].month_count) + (arr_subscription[sub_type - 1].year_count)))) {
						year = true;
						arr_users[user - 1].sub.plan_type = "year";
						arr_users[user - 1].sub.duriation_plan_type = arr_subscription[sub_type - 1].year_sub[planvar - 1].duration;
						arr_users[user - 1].sub.Num_trips = arr_subscription[sub_type - 1].year_sub[planvar - 1].no_of_trips;
						arr_users[user - 1].sub.remaining_trips = arr_users[user - 1].sub.Num_trips;
						break;
					}
					else {
						cout << "\n This plan is not available \n";
						continue;
					}
				}

				int zone_var;
				if (month) {
					cout << " Please choose your zone \n";
					for (int i = 0;i < 4;i++) {
						cout << "For Zone " << i + 1
							<< " : "
							<< arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[i]
							<< " LE" << "  " << endl;
					}
					cout << endl;
					cout << "your choice is -->  ";
					cin >> zone_var;
					cin.ignore();

					if (arr_users[user - 1].balance >= arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1])
					{
						arr_users[user - 1].balance -= arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1];
						arr_users[user - 1].sub.zone = zone_var;
						arr_users[user - 1].sub.zonePrice = arr_subscription[sub_type - 1].month_sub[planvar - 1].zonesPrice[zone_var - 1];
						finished = true;
					}
					else {
						cout << "\nthe balance for this user is too low please recharge it \n";
						recharge();
						continue;

					}
				}
				else if (year) {
					cout << " Please choose your zone \n";
					for (int i = 0;i < 4;i++) {
						cout << "For Zone " << i + 1
							<< " : "
							<< arr_subscription[sub_type - 1].year_sub[planvar - 2].zonesPrice[i]
							<< " LE" << "  " << endl;
					}
					cout << endl;
					cout << "your choice is -->  ";
					cin >> zone_var;
					cin.ignore();
					if (arr_users[user - 1].balance >= arr_subscription[sub_type - 1].year_sub[planvar - 2].zonesPrice[zone_var - 1])
					{
						arr_users[user - 1].balance -= arr_subscription[sub_type - 1].year_sub[planvar - 2].zonesPrice[zone_var - 1];
						arr_users[user - 1].sub.zone = zone_var;
						arr_users[user - 1].sub.zonePrice = arr_subscription[sub_type - 1].year_sub[planvar - 2].zonesPrice[zone_var - 1];
						finished = true;
					}
					else {
						cout << "\nthe balance for this user is too low please recharge it \n";
						recharge();
						continue;
					}

				}
				indexofuser = user - 1;

				finalize_subscription();
			}
			while ((arr_subscription[sub_type - 1].fixed == 'n')) {
				arr_users[user - 1].sub.plan_type = "wallet";
				int balancewallt;
				bool multiple = true;
				arr_users[user - 1].sub.expiry = "0";
				arr_users[user - 1].sub.remaining_trips = 0;
				arr_users[user - 1].sub.fixed = 'n';
				arr_users[user - 1].sub.duriation_plan_type = 0;
				arr_users[user - 1].sub.Num_trips = 0;
				arr_users[user - 1].sub.zone = 0;
				arr_users[user - 1].sub.zonePrice = 0;

				cout << "\n please enter your balance in the " << arr_subscription[sub_type - 1].plan_name << " : ";

				cin >> balancewallt;

				if (balancewallt <= arr_users[user - 1].balance)
				{
					if (balancewallt <= arr_subscription[sub_type - 1].wallet_sub.card_balance) {
						if (balancewallt % arr_subscription[sub_type - 1].wallet_sub.fund_multiple == 0) {
							multiple = false;
							arr_users[user - 1].sub.balancew = balancewallt;
							arr_users[user - 1].balance -= balancewallt;
						}
						if (multiple) {
							cout << "\n Please enter a number multiple of : " << arr_subscription[sub_type - 1].wallet_sub.fund_multiple;
							continue;
						}
					}
					else {
						cout << "\nthis balance is bigger than balance card for this wallet\n"
							<< "\nPlease enter a number less than : " << arr_subscription[sub_type - 1].wallet_sub.card_balance;
						continue;
					}

					finished = true;
					indexofuser = user - 1;
					setActivationDate();
					break;

				}
				else
				{
					int newbalance = 0;
					cout << "\nThe balance for this user is too low please recharge it \n";
					cout << "\nplease enter your balance that you want to recharge : ";
					cin >> newbalance;
					arr_users[user - 1].balance += newbalance;
					cout << "the user current balance is : " << arr_users[user - 1].balance << endl;
					continue;
				}

			}
			if (finished)
			{
				break;
			}
		}


		else if (subscans == 2) {
			int newbalance;
			cout << "The balnce for this user is : ";
			cout << arr_users[user - 1].balance << endl;
			cout << "Enter the new balance : ";
			cin >> newbalance;
			cout << "you charged the balance successfully \n";
			arr_users[user - 1].balance += newbalance;
			cout << "your current balance now is : "
				<< arr_users[user - 1].balance;
			break;
		}
		else {
			cout << "\n Invalid choice please try again\n";
			continue;
		}

	}
}

bool isValidUserInput(int userNumber) {
	if (userNumber < 1 || userNumber > number_of_users_in_array) {
		cout << "Invalid position. Please enter a number between 1 and " << number_of_users_in_array << "." << endl;
		return false;
	}
	return true;
}

void removeUser() {
	int userNumber; string separator = "_";

	cout << "\n" << separator << endl;
	cout << "Enter the user position to delete (1-based): ";

	while (true) {//to check admin input is digit
		cin >> userNumber;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid number." << endl;
		}
		else if (!isValidUserInput(userNumber)) {
			cout << "Please enter a valid user position (1-based): ";
		}
		else {
			break;
		}
	}

	int index = userNumber + 1;

	string deletedName = arr_users[index].username;
	string deletedID = arr_users[index].id;

	cout << "\n" << separator << endl;
	cout << "Deleting user: " << deletedName << " (ID: " << deletedID << ")" << endl;

	// shifting array
	for (int i = index; i < number_of_users_in_array - 1; ++i) {
		arr_users[i] = arr_users[i + 1];
	}

	number_of_users_in_array--;  // Decrease the count of users

	cout << "\nUser has been deleted successfully." << endl;
	cout << "Deleted user: " << deletedName << " (ID: " << deletedID << ")" << endl;
	cout << separator << endl;

	cout << "\nRemaining users count: " << number_of_users_in_array << endl;
	cout << "\n" << separator << endl;
}

void admin_change_users()
{
	string line(40, '_');  string choice, DesireToContinue; bool repeat = 0;
	do
	{
		repeat = 0;

		cout << "\nChoose the choice you want to perform \n" << line << endl << endl;
		cout << "Press[ 1 ] to view profiles of users .\n\nPress[ 2 ] to modify users profiles .\n\n"
			<< "Press[ 3 ] to delete profiles ." << endl;
		cout << "\nYour choice ---> ";   cin >> choice;
		while (choice != "1" && choice != "2" && choice != "3")
		{
			cout << "Invalid number , please Enter a proper choice !!!\nyour choice ---> ";  cin >> choice;
		}

		if (choice == "1")
		{
			view_users_toAdmin();
			cout << "\n\nPress[ 1 ] to continue program .\nPress[ 2 ] to close this page .\nYour choice ---> ";
			cin >> choice;
			if (choice == "1")
			{
				repeat = 1; continue;
			}
			else if (choice == "2")
			{
				break;
			}


		}
		else if (choice == "2")
		{
			admin_change_user_subsc();

		}
		else if (choice == "3")
		{
			removeUser();
		}

		cout << "\nDo you want to do more operations \? [ y -->(yes) / n -->(no) ]\nYour choice ---> "; cin >> DesireToContinue;
		while ((DesireToContinue != "y" && DesireToContinue != "Y" && DesireToContinue != "n" && DesireToContinue != "N") || DesireToContinue.size() != 1)
		{
			cout << "Invalid answer , please Enter ( y - n )\nYour choice ---> "; cin >> DesireToContinue;
		}

		if (DesireToContinue == "y" || DesireToContinue == "Y")
		{
			repeat = 1;
		}

	} while (repeat);

}

//////////////files//////////////

void load_all() {
	ReadFromFile();
	load_subsc_data();
	load_user_subsc();
	loadRideHist();
	read_stations();

}

void save_all_data() {
	saveusersinfo();
	save_user_subsc();
	save_subsc_data();
	save_rides_to_file();
	stations2file();
}


void bye_bye() {
	cout << "\n\t\t\tThank you for using our Cairo Ride program \t\t\t\n"
		<< "\t\t\t\t Have a nice Ride \t\t\t\n";
}

void insights_subs() {
	int maxindex = -1;
	int maxvalue = -1;
	for (int k = 0;k < num_of_subsc;k++) {
		for (int i = 0;i < number_of_users_in_array;i++)
		{
			if (arr_users[i].sub.subscription_type == arr_subscription[k].plan_name)
			{
				arr_sub_insights[k]++;
			}
		}
	}

	for (int l = 0;l < num_of_subsc;l++)
	{

		if (arr_sub_insights[l] > maxvalue)
		{
			maxvalue = arr_sub_insights[l];
			maxindex = l;
		}

	}

	cout << "this is the most subscription used in this program : " << arr_subscription[maxindex].plan_name << endl;
	system("pause");
}

int main() {

	load_all();

	while (true)
	{
		bool admin_exit = false;
		bool admin_logout = false;
		bool seclogout = false;
		int ans = HelloFunction();
		system("cls");

		if (ans == 1)
		{

			sign = newaccount();
			indexofuser = number_of_users_in_array - 1;
			finalize_subscription();
			system("cls");
		}
		else if (ans == 2)
		{
			sign = SignInFun(realadmin_by_keypass);
		}
		bool Firstlogout = false;

		while (arr_users[indexofuser].admin_role == 0) {
			if (sign && (arr_users[indexofuser].admin_role == 0))
			{
				system("cls");  ///--> clear screen

				cout << "\n\n Welcome " << arr_users[indexofuser].username
					<< "\n " << uscores
					<< "\n * For personal details press [ 1 ] .\n\n"
					<< "\n * For New Ride or Rides History press[ 2 ] .\n\n"
					<< "\n * For subscriptions settings press[ 3 ] .\n\n"
					<< "\n * To Logout press [ 4 ] .\n\n"
					<< "\n * For exit the program press [ 5 ].\n\n";
				int log_var;
				cout << " * Your choice is -->  ";
				cin >> log_var;
				system("cls");

				switch (log_var) {
				case 1:
					Edit(); system("pause");
					break;
				case 2:int Ride_var;
					cout << "\n * For New Ride press [ 1 ] .\n"
						<< "\n * For Rides History press [ 2 ] .\n"
						<< "\n * Your choice is --> ";
					cin >> Ride_var;
					system("cls");
					if (Ride_var == 1)
						metro_lines();
					else
					{
						DisplayHistoryRides();
						system("pause");
					}
					break;
				case 3:

					manage_plan();break;

				case 4:
					Firstlogout = true;
					break;
				case 5:seclogout = true;
					Firstlogout = true;
					break;

				default:
					cout << "\n\t\t\t Invalid choice please try again .\t\t\t \n";
				}
			}
			if (Firstlogout)
			{
				/// if we want to close program 
				break;
			}
		}

		if (seclogout)   ///  if we want to close program
		{
			break;
		}

		if (realadmin_by_keypass) {
			while (true) {
				system("cls");
				int admin_ans;

				cout << "\nFor subscription settings press: 1 \n"
					<< "\nFor user settings press: 2 \n"
					<< "\nFor rides settings press: 3\n"
					<< "\nFor show the most subscription used in the program press: 4\n"
					<< "\nFor logout : 5\n"
					<< "\nFor exit system : 6\n";
				cin >> admin_ans;
				cin.ignore(1000, '\n');
				switch (admin_ans) {
				case 1:
					int choice;
					do {
						cout << "\n====== Subscription Management ======\n";
						cout << "\n1. Add new subscription\n";
						cout << "\n2. View subscriptions\n";
						cout << "\n3. Delete a subscription\n";
						cout << "\n4. Edit a subscription\n";
						cout << "\n5. Exit\n";
						cout << "\nChoose an option: ";
						cin >> choice;
						cin.ignore();

						switch (choice) {
						case 1:
							add(num_of_subsc);
							break;
						case 2:
							view(num_of_subsc);
							break;
						case 3:
							delete_sub(num_of_subsc);
							break;
						case 4:
							modify(num_of_subsc);
							break;
						case 5:
							cout << "Exiting subscription management" << endl;
							break;
						default:
							cout << "Invalid option please try again" << endl;
							break;
						}

					} while (choice != 5);
					break;
				case 2:admin_change_users();break;
				case 3:admin_rides();break;
				case 4:insights_subs();break;
				case 5:admin_logout = true;break;
				case 6:admin_exit = true;break;
				default:
					cout << "\nInvalid answer please choose one from the appove choices ";
					continue;

				}
				if (admin_logout || admin_exit) {
					break;
				}

			}
			if (admin_logout)
			{
				system("cls");
				continue;
			}
			if (admin_exit)
			{
				system("cls");
				break;
			}
		}
	}
	bye_bye();
	save_all_data();
	return 0;
}