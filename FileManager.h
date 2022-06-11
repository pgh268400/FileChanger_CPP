#include <iostream>
#include <string>
#include <vector>

//avoid using namespace std
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;


class FileManager {
public:
	//User Interface

	FileManager() = delete; //�⺻ �����ڴ� ����(����)
	FileManager(string dir_path); //������

	//Getter()
	int get_file_count() const; 
	int get_dir_count() const;
	int get_all_count() const;

	//print
	void print_file_list();
	void print_dir_list();
	void print_all_list();

	//replace (���� ���ϸ�)
	void replace_file_name(string& find, string& replace);
	void insert_left_file_name(string& insert_str);
	void insert_right_file_name(string& insert_str);

	//���丮��
	void replace_dir_name(string& find, string& replace);
	void insert_left_dir_name(string& insert_str);
	void insert_right_dir_name(string& insert_str);

	//����
	void replace_all_name(string& find, string& replace);
	void insert_left_all_name(string& insert_str);
	void insert_right_all_name(string& insert_str);


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