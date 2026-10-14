#include "coins.hpp"
#include <iostream>
using namespace std;

constexpr int CENTS_PER_DOLLAR = 100;

// Constructor: member initializer list
Coins::Coins(int q, int d, int n, int p)
    : quarters{q}, dimes{d}, nickels{n}, pennies{p} {}

// Move all coins from 'coins' into this, then empty 'coins'
void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    dimes += coins.dimes;
    nickels += coins.nickels;
    pennies += coins.pennies;
    coins = Coins(0, 0, 0, 0);
}

// Enough of EACH denomination?
bool Coins::has_exact_change_for_coins(const Coins& coins) const {
    return quarters >= coins.quarters && dimes >= coins.dimes &&
           nickels >= coins.nickels && pennies >= coins.pennies;
}

// Check first, modify only if valid
Coins Coins::extract_exact_change(const Coins& coins) {
    bool negative = coins.quarters < 0 || coins.dimes < 0 ||
                    coins.nickels < 0 || coins.pennies < 0;
    if (negative || !has_exact_change_for_coins(coins)) {
        return Coins(0, 0, 0, 0);
    }
    quarters -= coins.quarters;
    dimes -= coins.dimes;
    nickels -= coins.nickels;
    pennies -= coins.pennies;
    return coins;
}

int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME +
           nickels * CENTS_PER_NICKEL + pennies;
}

void Coins::print(ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, "
        << nickels << " nickels, " << pennies << " pennies";
}

ostream& operator<<(ostream& out, const Coins& coins) {
    coins.print(out);
    return out;
}

// Greedy: quarters first, then dimes, nickels, pennies
Coins coins_required_for_cents(int amount_in_cents) {
    int q = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    int d = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    int n = amount_in_cents / CENTS_PER_NICKEL;
    int p = amount_in_cents % CENTS_PER_NICKEL;
    return Coins(q, d, n, p);
}

// $x.xx, always two digits after the point
void print_cents(int cents, ostream& out) {
    int rest = cents % CENTS_PER_DOLLAR;
    out << '$' << cents / CENTS_PER_DOLLAR << '.';
    if (rest < 10) out << '0';
    out << rest;
}

Coins ask_for_coins(istream& in, ostream& out) {
    int q = 0, d = 0, n = 0, p = 0;
    out << "Quarters? "; in >> q;
    out << "Dimes? ";    in >> d;
    out << "Nickels? ";  in >> n;
    out << "Pennies? ";  in >> p;
    return Coins(q, d, n, p);
}

void coins_menu(istream& in, ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    while (true) {
        out << "\n1. Deposit\n2. Extract\n3. Print balance\n4. Exit\nChoice? ";
        int choice;
        if (!(in >> choice)) return;   // stop on end of input
        if (choice == 1) {
            Coins c = ask_for_coins(in, out);
            myCoins.deposit_coins(c);
        } else if (choice == 2) {
            Coins req = ask_for_coins(in, out);
            if (myCoins.has_exact_change_for_coins(req)) {
                out << "Extracted " << myCoins.extract_exact_change(req) << endl;
            } else {
                out << "ERROR: not enough coins" << endl;
            }
        } else if (choice == 3) {
            print_cents(myCoins.total_value_in_cents(), out);
            out << endl;
        } else if (choice == 4) {
            return;
        } else {
            out << "Invalid choice" << endl;
        }
    }
}
