#include <iostream>
#include <string>
#include <vector>

//avoid using namespace std
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

//��� ������ FileType
enum class FileType {
	File, Directory, All
};

class FileManager {
public:
	//User Interface

	FileManager() = delete; //�⺻ �����ڴ� ����(����)
	FileManager(string dir_path); //������

	//Getter()
	int get_count(FileType ft) const;

	//print
	void print_list(FileType ft);
	void replace_name(FileType ft, string& find, string& replace); //�����ε�
	void insert_left_name(FileType ft, string& insert_str); //�����ε�
	void insert_right_name(FileType ft, string& insert_str); //�����ε�

private:
	//Encapsulation

	//��� ���� ��
	string dir_path;

	//���� ����, ���丮 ����, ��� ���� ����
	int file_count, dir_count, all_count;

	//���丮�� ����, ���� ��ϵ�
	vector<string> file_list;
	vector<string> dir_list;

	//���ڿ� ����, ġȯ �Լ�
	void replace_name(vector<string>& lst, string& find, string& replace);
	void insert_left_name(vector<string>& lst, string& insert_str);
	void insert_right_name(vector<string>& lst, string& insert_str);

	void insert_last_symbol(string& path);
	string ReplaceAll(string& str, const std::string& from, const std::string& to);
};