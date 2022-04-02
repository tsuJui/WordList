#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int para_n = 0;  // 1代表传入该类型参数
int para_w = 0;
int para_m = 0;
int para_c = 0;
int para_h = 0;
string h_sub;
int para_t = 0;
string t_sub;
int para_r = 0;
int ring_warn = 0;

int output(char* result[], int paraN, int paraM, int paraW, int paraC) {
  int count = 0;  //记录要求的值的数量，比如单词数量或者字母数量或者单词链数量
  int sumCount = 0;  //记录result数组使用长度
  int i = 0;

  if (paraN == 1) {  //输出到控制台的情况
    count = 0;
    sumCount = 0;
    while (result[sumCount][0] != '\0') {
      sumCount++;
      count++;
    }
    if (sumCount > 20000) {
      cout << "the number of wordlists is too big, over 20000" << endl;
      return count;
    } else {
      sumCount = 0;
      cout << count << endl;
      while (sumCount < count) {
        cout << result[sumCount] << endl;
        sumCount++;
      }
      return count;
    }
  } else {  //输出到文件的情况
    ofstream outFile;
    outFile.open("solution.txt", ios::out);  //输出到solution文件当中
    if (paraM == 1) {
      count = 0;
      sumCount = 0;
      while (result[sumCount][0] != '\0') {
        sumCount++;
        count++;
      }
      if (sumCount > 20000) {
        cout << "the number of words in the wordlist is too big, over 20000"
             << endl;
        outFile.close();
        return count;
      } else {
        sumCount = 0;
        while (sumCount < count) {
          outFile << result[sumCount] << endl;
          sumCount++;
        }
        outFile.close();  //关闭对象与文件间的关联
        return count;
      }
    } else if (paraW == 1) {  //与上一个一样判断
      count = 0;
      sumCount = 0;
      while (result[sumCount][0] != '\0') {
        sumCount++;
        count++;
      }
      if (sumCount > 20000) {
        cout << "the number of words in the wordlist is too big, over 20000"
             << endl;
        outFile.close();
        return count;
      } else {
        sumCount = 0;
        while (sumCount < count) {
          outFile << result[sumCount] << endl;
          sumCount++;
        }
        outFile.close();  //关闭对象与文件间的关联
        return count;
      }
    } else if (paraC == 1) {  // count记录字母数量
      count = 0;
      sumCount = 0;
      i = 0;
      while (result[sumCount][0] != '\0') {
        i = 0;
        while (result[sumCount][i] != '\0') {
          i++;
          count++;
        }
        sumCount++;
      }
      if (sumCount > 20000) {
        cout << "the number of words in the wordlist is too big, over 20000"
             << endl;
        outFile.close();
        return count;
      } else {
        i = 0;
        while (i < sumCount) {
          outFile << result[i] << endl;
          i++;
        }
        outFile.close();  //关闭对象与文件间的关联
        return count;
      }
    } else {
      cout << "error in output!" << endl;
      return -1;
    }
  }
}

char to_lower(char c) {
  return tolower(c);
}

char to_upper(char c) {
  return toupper(c);
}
int findPos(string word, vector<string>& a, int begin, int end) {    //用二分法查找位置，开始查找位置，结束查找位置
  if (begin == end) {
    if (word == a[begin]) {
      return -1;
    } else if (word > a[begin]) {
      return end + 1;
    } else {
      return begin;
    }
  }
  if (end - begin == 1) {
    if (word == a[begin]) {   //word在此位置前
      return -1;           //单词重复
    } else if (word == a[end]) {
      return -1;           //单词重复
    } else if (word < a[begin]) {
      return begin;
    } else if (word > a[end]) {
      return end + 1;
    } else {
      return end;
    }
  } else {
    int m = (begin + end) / 2;
    if (word == a[m]) {
      return -1;          //单词重复
    } else if (word < a[m]) {
      return findPos(word, a, begin, m);
    } else {
      return findPos(word, a, m, end);
    }
  }
  cout << "error in function findPos: " << word << " " << begin << "  " << end << endl;    //报错
  return -2;
}

bool contains(vector<string>& list, string word) {
  for (int i = 0; i < list.size(); i++) {
    if (list[i] == word) {
      return true;
    }
  }
  return false;
}

void countWordList(vector<string>& list, string word,
                             vector<vector<string>>& ordered) { //得到最长单词链
  int k = word.back() - 'a';
  if (ring_warn == 1) {
    return;
  }
  for (int i = 0; i < ordered[k].size(); i++) {
    if (!contains(list, ordered[k][i])) {
      if (para_r != 1) {
        if (ordered[k][i].back() == list[0].front()) {
          ring_warn = 1;
          return;
        }
      }
      list.push_back(ordered[k][i]);
      countWordList(list, list.back(), ordered);
      return;
    }
  }
}

int main(int argc, char* argv[]) {
  HMODULE module = LoadLibrary("core.dll");
  if (module == NULL) {
    printf("load core.dll failed\n");
    return 1;
  }
  typedef int (*chain_word)(char*[], int, char*[], char, char, bool);
  typedef int (*chain_all)(char*[], int, char*[]);
  typedef int (*chain_word_unique)(char*[], int, char*[]);
  typedef int (*chain_char)(char*[], int, char*[], char, char, bool);
  chain_word gen_chain_word;
  chain_all gen_chains_all;
  chain_word_unique gen_chain_word_unique;
  chain_char gen_chain_char;
  gen_chain_word = (chain_word)GetProcAddress(module, "gen_chain_word");
  gen_chains_all = (chain_all)GetProcAddress(module, "gen_chains_all");
  gen_chain_word_unique = (chain_word_unique)GetProcAddress(module, "gen_chain_word_unique");
  gen_chain_char = (chain_char)GetProcAddress(module, "gen_chain_char");
                         
  fstream inFile;
  string fileName = "";  //打开文件名
  for (int i = 1; i < argc; i++) {
    string str = argv[i];
    if (str == "-n") {
      if (para_n == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_n = 1;
    } else if (str == "-w") {
      if (para_w == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_w = 1;
    } else if (str == "-m") {
      if (para_m == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_m = 1;
    } else if (str == "-c") {
      if (para_c == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_c = 1;
    } else if (str == "-h") {
      if (para_h == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      if (i < argc - 1) {
        h_sub = argv[++i];
      } else {
        cout << "Head Letter Wrong!" << endl;
        return 1;
      }
      if (h_sub.length() > 1) {
        cout << "Head Letter Too Long!" << endl;
        return 1;
      }
      if (!((h_sub.at(0) >= 'a' && h_sub.at(0) <= 'z') ||
            (h_sub.at(0) >= 'A' && h_sub.at(0) <= 'Z'))) {
        cout << "Head Letter Wrong!" << endl;
        return 1;
      }
      para_h = 1;
    } else if (str == "-t") {
      if (para_t == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      if (i < argc - 1) {
        t_sub = argv[++i];
      } else {
        cout << "Tail Letter Wrong!" << endl;
        return 1;
      }
      if (t_sub.length() > 1) {
        cout << "Tail Letter Too Long!" << endl;
        return 1;
      }
      if (!((t_sub.at(0) >= 'a' && t_sub.at(0) <= 'z') ||
            (t_sub.at(0) >= 'A' && t_sub.at(0) <= 'Z'))) {
        cout << "Tail Letter Wrong!" << endl;
        return 1;
      }
      para_t = 1;
    } else if (str == "-r") {
      if (para_r == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_r = 1;
    } else if (str.length() >= 4) {
      if (str.substr(str.length() - 4) == ".txt") {
        if (fileName != "") {
          cout << "Multiple Files Error!" << endl;
          return 1;
        }
        fileName = str;
      } else {
        cout << str << endl;
        cout << "Unrecognizable Information Error!" << endl;
        return 1;
      }
    } else {
      cout << "Unrecognizable Parameter Error!" << endl;
      return 1;
    }
  }
  if (fileName == "") {
    cout << "No File Error!" << endl;
    return 1;
  }
  if (para_n + para_m + para_w + para_c == 0) {
    cout << "No Parameter Error!" << endl;
    return 1;
  }
  if (para_n + para_m + para_w + para_c > 1) {
    cout << "Conflict Parameters Error!" << endl;
    return 1;
  }
  if (para_n == 1 && para_h + para_t + para_r > 1) {
    cout << "Conflict Parameters Error!" << endl;
    return 1;
  }
  inFile.open(fileName, ios::in);
  if (!inFile.is_open()) {  //判断文件是否成功打开
    cout << "Can't find the file!" << endl;
    return 1;
  }
  vector<string> lowWordsList;  //小写单词
  string line;                  //此行的字符串
  string word;                  //单词截取
  int pos = 0;                  //记录位置
  while (!inFile.eof()) {       //直到文件末尾
    getline(inFile, line);      //得到一行单词
    pos = 0;
    while (pos < line.length()) {   //这里length和size应该都可
      word = "";                    //重置word
      if (isalpha(line.at(pos))) {  //这里line[pos]和line.at(pos)应该等价
        while (isalpha(line.at(pos))) {
          word += line.at(pos);
          pos++;
          if (pos < line.length())  //判断是否越界，避免报错
            continue;
          else
            break;
        }
        if (word.length() <= 1) {  //一个字母就跳过
          // cout << "a letter can't be a word!" << endl;
          continue;
        }

        transform(word.begin(), word.end(), word.begin(), to_lower);  //变成小写
        // cout << word << "------------" << endl;
        if (lowWordsList.size() == 0) {
          lowWordsList.push_back(word);
          continue;
        }
        int index = findPos(word, lowWordsList, 0, lowWordsList.size() - 1);
        // cout << index << "\n" << endl;
        if (index < 0) {
          continue;
        } else if (index >= lowWordsList.size()) {
          lowWordsList.push_back(word);  //小写字母，直接加到最后
        } else {
          lowWordsList.insert(lowWordsList.begin() + index,
                              word);  //小写字母，插入
        }
      } else {  //不论是否是字母，都得pos++
        pos++;
      }
    }
  }
  inFile.close();
  char* words[20010]{};
  int i = 0;
  while (i < lowWordsList.size()) {
    words[i] = (char*)malloc(sizeof(char) * 50);
    i++;
  }
  i = 0;
  while (i < lowWordsList.size()) {
    int j = 0;
    if (words[i]) {
      while (j < lowWordsList[i].length()) {
        words[i][j] = lowWordsList[i].at(j);
        j++;
      }
      words[i][j] = '\0';
    }
    i++;
  }
  char* result[20010]{};
  i = 0;
  char head = 0;
  char tail = 0;
  bool enable_loop = false;
  if (para_r == 1) {
    enable_loop = true;
  }
  if (para_h == 1) {
    head = h_sub.at(0);
    head = tolower(head);
  }
  if (para_t == 1) {
    tail = t_sub.at(0);
    tail = tolower(tail);
  }
  if (para_w == 1) {
    int sum = gen_chain_word(words, lowWordsList.size(), result, head, tail,
                             enable_loop);
  } else if (para_n == 1) {
    int sum = gen_chains_all(words, lowWordsList.size(), result);
  } else if (para_m == 1) {
    int sum = gen_chain_word_unique(words, lowWordsList.size(), result);
  } else if (para_c == 1) {
    int sum = gen_chain_char(words, lowWordsList.size(), result, head, tail,
                             enable_loop);
  }
  output(result, para_n, para_m, para_w, para_c);
  for (int i = 0; i < 20010; i++) {
    free(words[i]);
    free(result[i]);
    i++;
  }
  return 0;
}