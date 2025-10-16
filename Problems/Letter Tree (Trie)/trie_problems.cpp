#include <bits/stdc++.h>
using namespace std;

class Trie {
 private:
  array<Trie *, 26> child{};
  bool isLeaf{};

 public:
  Trie() : child{}, isLeaf{} { child.fill(nullptr); };

  void insert(const string &str, int idx = 0) {
    // Recursive insertion
    // str == "car"
    if (idx == (int)str.size()) {
      isLeaf = true;
      return;
    }
    int current = str[idx] - 'a';
    if (!child[current]) {
      child[current] = new Trie;
    }
    child[current]->insert(str, idx + 1);
  }
  bool complete_word_exist(const string &str, int idx = 0) {
    if (idx == (int)str.size()) {
      return isLeaf == true;
    }
    int current = str[idx] - 'a';
    if (child[current] == nullptr) return false;
    return child[current]->complete_word_exist(str, idx + 1);
  };

  bool prefix_word_exist(const string &str, int idx = 0) {
    if (idx == (int)str.size()) {
      return true;
    }
    int current = str[idx] - 'a';
    if (child[current] == nullptr) return false;
    return child[current]->prefix_word_exist(str, idx + 1);
  }
  // Easy Problems
  void insert_i(string str) {
    Trie *trie = this;
    for (auto &ch : str) {
      int current = ch - 'a';
      if (!trie->child[current]) {
        trie->child[current] = new Trie;
      }
      trie = trie->child[current];
    }
    trie->isLeaf = true;
  };
  bool word_exist_i(string str) {
    Trie *trie = this;
    for (auto &ch : str) {
      int current = ch - 'a';
      if (!trie->child[current]) {
        return false;
      }
      trie = trie->child[current];
    }
    return trie->isLeaf;
  };

  string first_word_prefix(const string &str) {
    // Minimal prefix problem
    string result;
    Trie *trie = this;
    for (auto &ch : str) {
      int current = ch - 'a';
      if (trie->child[current]) {
        result += ch;
      } else {
        break;
      }
      trie = trie->child[current];
    }
    return result;
  }
  // For this, Make a class suffix Trie on it's own -> Store words in reverse
  static bool suffix_exist(string str) {
    // So, if we have "cart" -> "art" and "rt" should return true
    return false;
  }
  // Medium Problems
  void collect(vector<string> &result, string current_string) {
    // it's DFS - In order
    if (isLeaf) {
      result.push_back(current_string);
    }
    for (int i = 0; i < (int)child.size(); i++) {
      if (child[i]) {
        char ch = 'a' + i;
        child[i]->collect(result, current_string + ch);
      }
    }
  }
  vector<string> get_all_strings() {
    // This is always cleaner and intuitive to do
    vector<string> result;
    collect(result, "");
    return result;
  }

  vector<string> auto_complete(string str) {
    vector<string> result;
    Trie *trie = this;
    // I want to stop at the right trie
    for (auto &ch : str) {
      if (trie->child[ch]) {
        trie = trie->child[ch];
      } else {
        return {};  // Word isn't here -> How to auto_complete this ->
                    // (adjhfasdkjfh??)
      }
    }
    trie->collect(result, str);
    return result;
  }

  // Hard Problems

  // Found it a bit hard -> Still not good at the trie
  // Leetcode Practice on it -> We need to ramp this up
};

class Trie_Map {
 private:
  // Why? Using array means Alot of space is wasted when we go deeper
  // using map<char,node> it will reserve the only the letters that are there
  // Instead of [-,-,-,a,-,-,c,-,-,-,r] you have [a,c,r] but in a tree structure
  // -> O(Log n) Time O(log265) if all letters are there (worst case) -> still
  // o(1)
  map<char, Trie_Map *> child{};
  bool isLeaf{};

 public:
  Trie_Map() : child{}, isLeaf{} {};

  void insert(const string &str, int idx = 0) {
    // Recursive insertion
    // str == "car"
    if (idx == (int)str.size()) {
      isLeaf = true;
      return;
    }
    const char &current = str[idx];
    if (child.find(current) == child.end()) {
      child[current] = new Trie_Map;
    }
    child[current]->insert(str, idx + 1);
  }
  bool complete_word_exist(const string &str, int idx = 0) {
    if (idx == (int)str.size()) {
      return isLeaf == true;
    }
    const char &current = str[idx];
    if (child.find(current) == child.end()) return false;
    return child[current]->complete_word_exist(str, idx + 1);
  };
};

class Trie_Os {
 private:
  map<string, Trie_Os *> child{};
  bool isLeaf{};

 public:
  Trie_Os() : child{}, isLeaf{} {};

  void insert(const vector<string> &path, int idx = 0) {
    if (idx == (int)path.size()) {
      isLeaf = true;
      return;
    }
    const string &current = path[idx];
    if (child.find(current) == child.end()) {
      child[current] = new Trie_Os;
    }
    child[current]->insert(path, idx + 1);
  }
  bool subpath_exist(const vector<string> &path, int idx = 0) {
    if (idx == (int)path.size()) {
      return isLeaf == true;
    }
    const string &current = path[idx];
    if (child.find(current) == child.end()) return false;
    return child[current]->subpath_exist(path, idx + 1);
  };
};

void testTrieBasic() {
  cout << "[Trie] Basic Insert & Search Test" << endl;
  Trie trie;
  trie.insert("car");
  trie.insert("cat");
  trie.insert("dog");
  cout << "car exists: " << trie.complete_word_exist("car") << endl;
  cout << "cat exists: " << trie.complete_word_exist("cat") << endl;
  cout << "dog exists: " << trie.complete_word_exist("dog") << endl;
  cout << "do not exist: " << trie.complete_word_exist("do") << endl;
  cout << "Prefix 'ca' exists: " << trie.prefix_word_exist("ca") << endl;
  cout << "Prefix 'do' exists: " << trie.prefix_word_exist("do") << endl;
  cout << "Prefix 'z' exists: " << trie.prefix_word_exist("z") << endl;
  cout << endl;

  cout << "[Trie] Iterative Insert & Search Test" << endl;
  Trie trie2;
  trie2.insert_i("apple");
  trie2.insert_i("app");
  trie2.insert_i("banana");
  cout << "apple exists: " << trie2.word_exist_i("apple") << endl;
  cout << "app exists: " << trie2.word_exist_i("app") << endl;
  cout << "banana exists: " << trie2.word_exist_i("banana") << endl;
  cout << "ban does not exist: " << trie2.word_exist_i("ban") << endl;
  cout << endl;

  cout << "[Trie] First Word Prefix Test" << endl;
  Trie trie3;
  trie3.insert("carpet");
  trie3.insert("car");
  trie3.insert("cartoon");
  string prefix = trie3.first_word_prefix("carpool");
  cout << "First word prefix for 'carpool': " << prefix << endl;
  prefix = trie3.first_word_prefix("cartoonist");
  cout << "First word prefix for 'cartoonist': " << prefix << endl;
  prefix = trie3.first_word_prefix("dog");
  cout << "First word prefix for 'dog': " << prefix << endl;
  cout << endl;
}

void testTrieMapBasic() {
  cout << "[Trie_Map] Basic Insert & Search Test" << endl;
  Trie_Map trieMap;
  trieMap.insert("apple");
  trieMap.insert("app");
  trieMap.insert("banana");
  cout << "apple exists: " << trieMap.complete_word_exist("apple") << endl;
  cout << "app exists: " << trieMap.complete_word_exist("app") << endl;
  cout << "banana exists: " << trieMap.complete_word_exist("banana") << endl;
  cout << "ban does not exist: " << trieMap.complete_word_exist("ban") << endl;
  cout << endl;
}

void testTrieOsBasic() {
  cout << "[Trie_Os] Basic Insert & Subpath Test" << endl;
  Trie_Os trieOs;
  vector<string> path1 = {"home", "user", "docs"};
  vector<string> path2 = {"home", "user", "pics"};
  trieOs.insert(path1);
  trieOs.insert(path2);
  cout << "home/user/docs exists: " << trieOs.subpath_exist(path1) << endl;
  cout << "home/user/pics exists: " << trieOs.subpath_exist(path2) << endl;
  vector<string> path3 = {"home", "user", "music"};
  cout << "home/user/music does not exist: " << trieOs.subpath_exist(path3)
       << endl;
  cout << endl;
}

int main() {
  testTrieBasic();
  testTrieMapBasic();
  testTrieOsBasic();
  return 0;
}