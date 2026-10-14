#include <iostream>
#include "coins.hpp"
using namespace std;

constexpr int CENTS_FOR_CHIPS = 149;
constexpr int CENTS_TO_TRANSFER = 405;

int main() {
    // Step 1: create two holders and print them
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);
    cout << "piggyBank: " << piggyBank << endl;
    cout << "pocket: " << pocket << endl;

    // Step 2: buy chips with coins from pocket
    Coins chips =
        pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CHIPS));
    cout << "Bought chips using " << chips << endl;

    // Step 3: transfer $4.05 from piggyBank to pocket
    Coins transfer =
        piggyBank.extract_exact_change(coins_required_for_cents(CENTS_TO_TRANSFER));
    cout << "Transferred " << transfer << " from piggyBank to pocket" << endl;
    pocket.deposit_coins(transfer);

    // Step 4: sofa change goes into piggyBank
    Coins sofa(10, 10, 10, 10);
    piggyBank.deposit_coins(sofa);
    cout << "sofa: " << sofa << endl;
    cout << "piggyBank: " << piggyBank << endl;

    // Step 5: final balance in dollars and cents
    cout << "piggyBank balance: ";
    print_cents(piggyBank.total_value_in_cents(), cout);
    cout << endl;
}
