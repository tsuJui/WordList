#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

char to_lower(char c) {
  return tolower(c);
}

char to_upper(char c) {
  return toupper(c);
}
vector<string> getWords(string line) {
  vector<string> wordsList;
  int pos = 0;
  string word = "";
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
      wordsList.push_back(word);
    } else {
      pos++;
    }
  }
  return wordsList;
}

vector<string> paraW(vector<string>& output) {  //输出一个包含单词最多的单词链
  string tmp = "";
  int count1 = 0;  //记录单词数量
  int count2 = 0;  //记录单词数量
  int i = 0;
  int j = 0;
  if (output.size() < 0) {  //防止output为空
    cout << "there is no wordList!" << endl;
    return getWords(tmp);
  }
  while (i < output.size()) {
    count2 = 0;
    j = 0;
    while (j < output[i].length()) {
      if (isalpha(output[i].at(j))) {  //[]和at()一致
        while (isalpha(output[i].at(j))) {
          j++;
          if (j < output[i].length())  //判断是否越界，避免报错
            continue;
          else
            break;
        }
        count2++;
      } else {
        j++;
      }
    }
    if (count2 > count1) {
      count1 = count2;
      tmp = output[i];
    }
    i++;
  }
  return getWords(tmp);
}

vector<string> paraM(
    vector<string>& output) {  //计算首字母不相同的含最多单词的单词链
  string tmp = "";
  int mark[26] = {0};  //标记首字母是否出现过
  int strMark = 0;     //标记该单词链是否满足要求
  int count1 = 0;      //记录单词数量
  int count2 = 0;      //记录单词数量
  int i = 0;
  int j = 0;
  if (output.size() <= 0) {  //防止output为空
    cout << "there is no wordList!" << endl;
    return getWords(tmp);
  }
  while (i < output.size()) {
    count2 = 0;
    strMark = 0;                //重置strMark
    for (j = 0; j < 26; j++) {  //重置mark
      mark[j] = 0;
    }
    j = 0;
    while (j < output[i].length()) {
      if (isalpha(output[i].at(j))) {  //[]和at()一致
        if (mark[output[i].at(j) - 'a'] == 1) {
          strMark = 1;
          break;
        } else {
          mark[output[i].at(j) - 'a'] = 1;
        }
        while (isalpha(output[i].at(j))) {
          j++;
          if (j < output[i].length())  //判断是否越界，避免报错
            continue;
          else
            break;
        }
        count2++;
      } else {
        j++;
      }
    }
    if (count2 > count1 && strMark == 0) {
      count1 = count2;
      tmp = output[i];
    }
    i++;
  }
  return getWords(tmp);
}

vector<string> paraC(vector<string>& output) {  //输出单词字母数量最多的单词链
  string tmp = "";
  int count1 = 0;  //记录字母数量
  int count2 = 0;  //记录字母数量
  int i = 0;
  int j = 0;
  if (output.size() < 0) {  //防止output为空
    cout << "there is no wordList!" << endl;
    return getWords(tmp);
  }
  while (i < output.size()) {
    count2 = 0;
    j = 0;
    while (j < output[i].length()) {
      if (isalpha(output[i].at(j))) {  //[]和at()一致
        j++;
        count2++;
      } else {
        j++;
      }
    }
    if (count2 > count1) {
      count1 = count2;
      tmp = output[i];
    }
    i++;
  }
  return getWords(tmp);
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
  fstream inFile;
  string fileName = "";  //打开文件名
  for (int i = 0; i < argc; i++) {
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
      h_sub = argv[++i];
      para_h = 1;
    } else if (str == "-t") {
      if (para_t == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      t_sub = argv[++i];
      para_t = 1;
    } else if (str == "-r") {
      if (para_r == 1) {
        cout << "Duplicate Parameter Error!" << endl;
        return 1;
      }
      para_r = 1;
    }
    if (str.length() >= 4) {
      if (str.substr(str.length() - 4) == ".txt") {
        fileName = str;
      }
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
        //cout << word << "------------" << endl;
        if (lowWordsList.size() == 0) {
          lowWordsList.push_back(word);
          continue;
        }
        int index = findPos(word, lowWordsList, 0, lowWordsList.size() - 1);
        //cout << index << "\n" << endl;
        if (index < 0) {
          continue;
        }
        else if (index >= lowWordsList.size()) {
          lowWordsList.push_back(word);  //小写字母，直接加到最后
        }
        else {
          lowWordsList.insert(lowWordsList.begin() + index, word);  //小写字母，插入
        }
      } else {                         //不论是否是字母，都得pos++
        pos++;
      }
    }
  }
  inFile.close();
  pos = 0;
  vector<vector<string>> ordered;//26个vector用于存放不同字母开头的单词
  for (int i = 0; i < 26; i++) {
    vector<string> tmp;
    ordered.push_back(tmp);
  }
  while (pos < lowWordsList.size()) {
    ordered[lowWordsList[pos].front() - 'a'].push_back(lowWordsList[pos]);
    pos++;
  }
  vector<string> output; //用于输出所有不含环单词链
  int sum = 0;
  for (int i = 0; i < lowWordsList.size(); i++) { //分割最长单词链
    vector<string> list;
    list.push_back(lowWordsList[i]);
    countWordList(list, lowWordsList[i], ordered);
    if (ring_warn == 1) {
      cout << "Contains Words Ring!" << endl; 
      return 1;
    }
    if (list.size() >= 2) {
      if (para_h == 1 && list[0].front() == h_sub.at(0)) {
        continue;
      }
      string str = list[0] + " ";
      for (int j = 1; j < list.size(); j++) {
        str = str + list[j] + " ";
        if (j == list.size() - 1 && para_t == 1 &&
            list[j].back() == t_sub.at(0)) {
          continue;
        }
        if (!contains(output, str)) {
          output.push_back(str);
        }
        sum++;
      }
    }
  }
  if (para_n == 1) {
    cout << sum << endl;
    for (int j = 0; j < output.size(); j++) {
      output[j].erase(output[j].end() - 1);
      cout << output[j] << endl;
    }
    return 0;
  }
  if (para_m == 1) {
    vector<string> out = paraM(output);
    ofstream outFile("solution.txt");
    for (int j = 0; j < out.size(); j++) {
      outFile << out[j] << endl;
    }
    outFile.close();
    return 0;
  }
  if (para_w == 1) {
    vector<string> out = paraW(output);
    ofstream outFile("solution.txt");
    for (int j = 0; j < out.size(); j++) {
      outFile << out[j] << endl;
    }
    outFile.close();
    return 0;
  }
  if (para_c == 1) {
    vector<string> out = paraC(output);
    ofstream outFile("solution.txt");
    for (int j = 0; j < out.size(); j++) {
      outFile << out[j] << endl;
    }
    outFile.close();
    return 0;
  }
  return 0;
}
