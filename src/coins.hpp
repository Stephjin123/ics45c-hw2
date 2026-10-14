// This "include guard" protects this header from being included twice:
#ifndef COINS_HPP
#define COINS_HPP

// <iosfwd> is a stripped-down version of <iostream>,
// usually enough for a header,
// but not enough to actually work with streams.
#include <iosfwd>

// Some useful constants for conversions -
// don't use magic numbers in your code!
constexpr int CENTS_PER_QUARTER = 25;
constexpr int CENTS_PER_DIME = 10;
constexpr int CENTS_PER_NICKEL = 5;

class Coins {
public:
  // Constructs 'this' Coins object so it has the number
  // of each coin given in the respective parameters.
  Coins(int q, int d, int n, int p);

  // Remove coins from 'coins' and put them into 'this' Coins object.
  void deposit_coins(Coins& coins);

  // Returns true only if 'this' Coins object has enough of each type of
  // coin to cover a possible extraction of the specific coins in 'coins'
  bool has_exact_change_for_coins(const Coins& coins) const;

  // Removes from 'this' Coins object the specific number of each type of
  // coin given in 'coins' and returns a 'Coins' object representing the
  // coins that were extracted.
  // For any invalid extraction request, return an empty Coins object
  // (0 of all coins).
  Coins extract_exact_change(const Coins& coins);

  // Returns how many cents the coins in 'this' object total,
  // e.g., 1,1,1,1 returns 41.
  int total_value_in_cents() const;

  // Prints the info in 'this' Coins object in the format
  // "6 quarters, 2 dimes, ...".
  // Always prints plural even for 1, e.g. "1 nickels".
  // This is the method called by the output stream inserter.
  void print(std::ostream& out) const;

  // Allows us to compare Coins objects by equality.
  // You *don't* have to implement anything here -
  // it's generated for you and useful for testing!
  bool operator==(const Coins& other) const = default;

private:
  int quarters, dimes, nickels, pennies;
};

// An appropriate output stream inserter for a Coins object.
std::ostream& operator<<(std::ostream& out, const Coins& coins);

// coins_required_for_cents() can use math or while loops
// to decide how to satisfy the need for amount_in_cents.
// First take as many quarters, then as many dimes, etc.
// E.g., coins_required_for_cents(117) returns Coins(4,1,1,2).
Coins coins_required_for_cents(int amount_in_cents);

// Prints the given number of cents in the format "$x.xx"
// to the given output stream.
// print_cents(3) prints "$0.03", print_cents(509) prints "$5.09",
// print_cents(97) prints "$0.97".
void print_cents(int cents, std::ostream& out);

// Asks for coins on output stream 'out' and reads the entered values
// on input stream 'in', then returns a Coins object with the coins
// that were entered. For example:
// "Quarters? 10"
// "Dimes? 5"
// "Nickels? 7"
// "Pennies? 237"
// -> function returns Coins(10,5,7,237)
Coins ask_for_coins(std::istream& in, std::ostream& out);

// Presents a coins menu on 'out' and reads input from 'in'.
// This handles deposits, extractions, and printing the balance.
// For precise requirements see Section 3.4.
void coins_menu(std::istream& in, std::ostream& out);

#endif  // End of the include guard.
