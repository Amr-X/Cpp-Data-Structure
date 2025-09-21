#include <bits/stdc++.h>
using namespace std;

// The main concern for me is to handle the overflow

// Will say n = 10 to make it easier
int hash_int(int value, int n = 10) { return value % n; }

// Starting with negative.. What to do?
// Result becomes negative number -> Can't Access array with

int hash_negative(int value, int n = 10) {
  return (value % n + n) % n;  // Shift to positive side and make sure we don't
                               // exceed n (if value is positive)
}

// Big numbers
int hash_string(string str, int n = 10) {
  // Number gets bigger and bigger and it overflows to the negative side
  int hashed_value = 0;
  for (auto &ch : str) {
    hashed_value =
        (hashed_value * 26 + (ch - 'a')) % n;  // Fix by %n with every iteration
  }
  return hashed_value;
}

////////////////
// Mid
////////////////

int hash_string_(string str, int n) {
  // Based on position
  int hashed_value = 0;

  for (int i = 0; i < (int)str.size(); i++) {
    hashed_value = (hashed_value + (str[i] * (i + 1))) % n;
  }

  return hashed_value;
}
int folding(string str, int n) {
  int sum{};
  for (int i = 0; i < (int)str.size(); i += 4) {
    string s = str.substr(i, 4);
    sum = (sum + hash_string_(s, n)) % n;
  }
  return sum;
}

struct obj {
  const static int INTERNAL_LIMIT = 2147483647;
  string str1, str2;
  int number;

  int hash() {
    // There is a lot of ways to do this!
    // Just watchout for the overflow that is it
    long long value = hash_string_(str1 + str2, INTERNAL_LIMIT);
    value += hash_int(number, INTERNAL_LIMIT) % INTERNAL_LIMIT;
    return value;
  }
};
// No need for 4 and 5
/////////////////////////////////////////////////////

/////////////////////////////
// Unordered set & map - Mid
/////////////////////////////

int count_unique_substrings(const string &str) {
  // how to get all substrings?
  unordered_set<string> seen;
  for (int i = 0; i < (int)str.size(); i++) {
    for (int j = i + 1; j <= (int)str.size(); j++) {
      string substr = str.substr(i, j - i);
      // Inserting duplicates will fail -> can even check return pair<it,bool>
      seen.insert(substr);
    }
  }
  return (int)seen.size();
  // A better DS is a trie
}

int count_substrings_match(const string &str1, const string &str2) {
  unordered_set<string> seen1;
  for (int i = 0; i < (int)str1.size(); i++) {
    for (int j = i + 1; j <= (int)str1.size(); j++) {
      string substr = str1.substr(i, j - i);
      seen1.insert(substr);
    }
  }
  unordered_set<string> matched;
  for (int i = 0; i < (int)str2.size(); i++) {
    for (int j = i + 1; j <= (int)str2.size(); j++) {
      string substr = str2.substr(i, j - i);
      if (!matched.count(substr) && seen1.count(substr)) {
        matched.insert(substr);
      };
    }
  }
  return (int)matched.size();
}
int unique_anagrams(const string &str) {
  unordered_set<string> seen;
  for (int i = 0; i < (int)str.size(); i++) {
    for (int j = i + 1; j <= (int)str.size(); j++) {
      string substr = str.substr(i, j - i);
      // Sorting will be the same thing
      sort(substr.begin(), substr.end());
      seen.insert(substr);
    }
  }
  return (int)seen.size();
}

// Problem 4 -> Hash the addresses of the nodes

int main() { return 0; }