#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  fstream inFile;
  string fileName = argv[argc - 1];  //打开文件名
  inFile.open(fileName, ios::in);
  if (!inFile.is_open()) {  //判断文件是否成功打开
    cout << "Can't find the file!" << endl;
    return 1;
  }
  vector<string> wordsList;     //存储单词
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
        wordsList.push_back(word);  //将单词加到wordsList后面
        transform(word.begin(), word.end(), word.begin(), tolower);
        lowWordsList.push_back(word);  //小写字母
      } else {                         //不论是否是字母，都得pos++
        pos++;
      }
    }
  }
  inFile.close();
  for (pos = 0; pos < wordsList.size(); pos++) {
    cout << wordsList[pos] << " " << lowWordsList[pos] << endl;
  }
  return 0;
}
