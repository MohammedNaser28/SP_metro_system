#include "global.h"

// Integer variables
int stationcnt = -1;
int real_zone = 0;
int balance = 0;
int ride_cnt = 0;
int num_stations = 0;
int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE] = { {0} };
int num_of_subsc = 0;
int kit_kat_index = 0;
int switching_index = 0;
int arr_sub_insights[1000] = { 0 };
int admin_chosen_user;
int chosenSubscriptionIndex = -1;
// Short integers
short indexofuser = 0;
short number_of_users_in_array = 0;
short hist_rides = 0;

// Boolean flags
bool DesireToCreateAcc = true;
bool sign = false;
bool realadmin_by_keypass = false;
bool why=false;
bool why_grater=false;
// User session strings
string name = "";
string password = "";
string current_user_id = "";

