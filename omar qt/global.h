#pragma once

#include "dependence.h"
#include <QString>
string getCurrentDate();
constexpr int usersnum = 1000;
constexpr int Size = 10000;
constexpr int MAX_rides = 10000;
constexpr int MAX_STATIONS_PER_LINE = 40;
constexpr int NUM_LINES = 3;
constexpr int MAX_GRAPH_SIZE = (MAX_STATIONS_PER_LINE * NUM_LINES) * 10;
const int MAX = (MAX_STATIONS_PER_LINE * NUM_LINES) * 10;
// Global variable declarations
extern int stationcnt;
extern int real_zone;
extern int balance;
extern int ride_cnt;
extern int num_stations;
extern int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
extern int num_of_subsc;
extern int kit_kat_index;
extern int switching_index;
extern int arr_sub_insights[1000];
extern int admin_chosen_user;
extern int chosenSubscriptionIndex ;
extern short indexofuser;
extern short number_of_users_in_array;
extern short hist_rides;

extern bool DesireToCreateAcc;
extern bool sign;
extern bool realadmin_by_keypass;
extern bool why;
extern bool why_grater;

extern string name;
extern string password;
extern string current_user_id;

