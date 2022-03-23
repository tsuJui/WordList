#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  fstream inFile;
  string fileName = argv[argc - 1];  //���ļ���
  inFile.open(fileName, ios::in);
  if (!inFile.is_open()) {  //�ж��ļ��Ƿ�ɹ���
    cout << "Can't find the file!" << endl;
    return 1;
  }
  vector<string> wordsList;     //�洢����
  vector<string> lowWordsList;  //Сд����
  string line;                  //���е��ַ���
  string word;                  //���ʽ�ȡ
  int pos = 0;                  //��¼λ��
  while (!inFile.eof()) {       //ֱ���ļ�ĩβ
    getline(inFile, line);      //�õ�һ�е���
    pos = 0;
    while (pos < line.length()) {   //����length��sizeӦ�ö���
      word = "";                    //����word
      if (isalpha(line.at(pos))) {  //����line[pos]��line.at(pos)Ӧ�õȼ�
        while (isalpha(line.at(pos))) {
          word += line.at(pos);
          pos++;
          if (pos < line.length())  //�ж��Ƿ�Խ�磬���ⱨ��
            continue;
          else
            break;
        }
        if (word.length() <= 1) {  //һ����ĸ������
          // cout << "a letter can't be a word!" << endl;
          continue;
        }
        wordsList.push_back(word);  //�����ʼӵ�wordsList����
        transform(word.begin(), word.end(), word.begin(), tolower);
        lowWordsList.push_back(word);  //Сд��ĸ
      } else {                         //�����Ƿ�����ĸ������pos++
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
