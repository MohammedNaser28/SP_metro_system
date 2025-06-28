#include "global.h"
#include "dependence.h"
#include "data.h"

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

				
			}
		}
	}
}