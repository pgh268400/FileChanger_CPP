#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;


class FileManager {
public:
	FileManager(string dir_path); //������
	int get_file_count() const; //Getter()

	void print_file_list();
	void replace_file_name(string find, string replace);
	void insert_left_file_name(string insert_str);
	void insert_right_file_name(string insert_str);

private:

	//��� ���� ��
	string dir_path;

	//���� ����
	int file_count;

	//���丮�� ����, ���� ��ϵ�
	vector<string> file_list;
	vector<string> dir_list;

	void insert_last_symbol(string& path);
	string ReplaceAll(string& str, const std::string& from, const std::string& to);
};