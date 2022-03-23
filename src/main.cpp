#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int main(int argc, char* argv[]) {
  fstream inFile;
  string fileName = argv[argc - 1];  //打开文件名
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
  while (pos < lowWordsList.size()) {
    cout << lowWordsList[pos] << endl;
    pos++;
  }
  return 0;
}
