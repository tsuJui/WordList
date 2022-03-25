# WordList
## user help
本程序实现了简易的单词链识别功能，通过在命令行输入对应指令来使用本程序。
指令格式为：程序名 参数 输入文件名（参数和文件名的顺序可以随意）
例：
> Wordlist.exe -n absolute_path_of_word_list

**参数说明**
-n 计算单词文本中可以构成多少个单词链（包含嵌套单词链），返回值为单词链总数和单词链。
-w 计算单词数量最多的单词链，如有多组则返回任意一组。
-m 计算单词数量最多的单词链（单词链中的每一个单词的首字母不能相同），如有多组则返回任意一组。
-c 计算字母最多的单词链，并输出
-h x 指定单词链首字母（x为任意小写字母）
-t x 指定单词链尾字母（x为任意小写字母）
-r 允许单词链中存在单词环
**错误类型说明**
|错误信息|错误说明|
|----|----|
|Duplicate Parameter Error!| 参数重复|
|Haed Letter Too Long!|h参数指定的字母超过一个|      
|Haed Letter Wrong!|h参数指定的字母不存在或者不是小写字母|
|Tail Letter Too Long!|t参数指定的字母超过一个|      
|Tail Letter Wrong!|t参数指定的字母不存在或者不是小写字母|
|Unrecognizable Information Error!|输入了非参数非文件名信息|
|Multiple Files Error!|输入了多个文件名|
|No File Error!|未输入文件名|
|No Parameter Error!|输入参数不包含输出类型参数|
|Conflict Parameters Error!|输出类型参数多于一个|
|Can't find the file!|无法打开文件，请检查该文件是否存在或者格式是否正确|
|Contains Words Ring!|文本内含有单词环|
