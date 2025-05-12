/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 2
* Programming Fundamentals Spring 2025
* Date: 02.02.2025
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "hcmcampaign.h"

using namespace std;

void g_satc_01() {
    cout << "----- Sample Testcase 01 -----" << endl;
    Configuration* config = new Configuration("config.txt");
    cout << config->str() << endl;
    delete config;
}
void g_satc_02() {
    cout << "----- Sample Testcase 02 -----" << endl;
    Vehicle tankOfLiber(20, 20, Position(1, 2), MORTAR); 
    Vehicle truckOfLiber(15, 10, Position(2, 2), TRUCK); // ATK = 5
    Infantry sniperOfLiber(10, 20, Position(1, 1), SNIPER); 

    Vehicle tankOfAr(5, 20, Position(3, 2), MORTAR);// ATK = 14
    Vehicle truckOfAr(1, 10, Position(3, 1), TRUCK);// ATK = 1
    Infantry sniperOfAr(7, 20, Position(3, 3), SNIPER);// ATK = 140

    Unit** unitArrayOfLiber = new Unit*[3];
    unitArrayOfLiber[0] = &tankOfLiber;
    unitArrayOfLiber[1] = &truckOfLiber;
    unitArrayOfLiber[2] = &sniperOfLiber; // LF = 29, EXP = 200

    Unit** unitArrayOfAr = new Unit*[3];
    unitArrayOfAr[0] = &tankOfAr;
    unitArrayOfAr[1] = &truckOfAr;
    unitArrayOfAr[2] = &sniperOfAr; // LF = 15, EXP = 180

    LiberationArmy* liberationArmy = new LiberationArmy(unitArrayOfLiber, 3, "LiberationArmy", 0);
    cout << liberationArmy->str() << endl;
    ARVN* arvn = new ARVN(unitArrayOfAr, 3, "ARVN", 0);
    cout << arvn->str() << endl;

    Army* enemyLiber = arvn;
    liberationArmy->fight(enemyLiber, false); // LF = 44, EXP = 300
    Army* enemyAr = liberationArmy;
    arvn->fight(enemyAr, false);

    cout << "* After the fight" << endl;
    Node* head = liberationArmy->get_unitList()->get_head();
    while (head){
        cout << head->data->str() << endl;;
        head = head->next;
    }
    cout << liberationArmy->str() << endl;
    cout << arvn->str() << endl;

    delete liberationArmy;
    delete arvn;
    delete[] unitArrayOfLiber;
    delete[] unitArrayOfAr;
}

int main(int argc, const char * argv[]) {
    g_satc_01();
    g_satc_02();
    return 0;
}
