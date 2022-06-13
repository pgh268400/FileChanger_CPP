#include <iostream>
#include "FileManager.h"
#include <filesystem>
#include <string>
#include "NatSort.hpp"


namespace fs = std::filesystem;


//��θ� �Է¹޾Ƽ� �ʱ�ȭ �ϴ� ������ �Լ�
FileManager::FileManager(string path)
{
	class unexpected_error{};
	//�������� üũ�ؼ� ����
	insert_last_symbol(path);

	//������ �ʱ�ȭ
	dir_path = path;


	for (const auto& entry : fs::directory_iterator(path))
	{
		std::error_code error_code; //���ܸ� ó������ �ʰ� error_code�� ������.
		bool isFile = fs::is_regular_file(entry.path(), error_code);

		string path = entry.path().string();
		if (isFile) { //�����ΰ��
			file_list.push_back(path);
		}
		else { //���丮�� ���
			dir_list.push_back(path);
		}
	}

	file_count = file_list.size();
	dir_count = dir_list.size();
	all_count = file_count + dir_count;

	//Natural Sort �˰������� ģ���ϰ� ���ĵ� ���� (Option)
	SI::natural::sort(file_list);
	SI::natural::sort(dir_list);
}

int FileManager::get_count(FileType ft) const
{
	if (ft == FileType::File) {
		return file_count;
	}
	else if (ft == FileType::Directory) {
		return dir_count;
	}
	else if (ft == FileType::All) {
		return all_count;
	}
}


void FileManager::print_list(FileType ft)
{
	if (ft == FileType::File) {
		for (string& element : file_list)
			cout << element << endl;
	}
	else if (ft == FileType::Directory) {
		for (string& element : dir_list)
			cout << element << endl;
	}
	else if (ft == FileType::All) {
		for (string& element : file_list)
			cout << element << endl;

		for (string& element : dir_list)
			cout << element << endl;
	}
}

void FileManager::replace_name(FileType ft, string& find, string& replace)
{
	if (ft == FileType::File) {
		replace_name(file_list, find, replace);
	}
	else if (ft == FileType::Directory) {
		replace_name(dir_list, find, replace);
	}
	else if (ft == FileType::All) {
		replace_name(file_list, find, replace);
		replace_name(dir_list, find, replace);
	}
}

void FileManager::insert_left_name(FileType ft, string& insert_str)
{
	if (ft == FileType::File) {
		insert_left_name(file_list, insert_str);
	}
	else if (ft == FileType::Directory) {
		insert_left_name(dir_list, insert_str);
	}
	else if (ft == FileType::All) {
		insert_left_name(file_list, insert_str);
		insert_left_name(dir_list, insert_str);
	}
}

void FileManager::insert_right_name(FileType ft, string& insert_str)
{
	if (ft == FileType::File) {
		insert_right_name(file_list, insert_str);
	}
	else if (ft == FileType::Directory) {
		insert_right_name(dir_list, insert_str);
	}
	else if (ft == FileType::All) {
		insert_right_name(file_list, insert_str);
		insert_right_name(dir_list, insert_str);
	}
}






void FileManager::replace_name(vector<string>& lst, string& find, string& replace)
{
	for (string& element : lst) { //element�� ���۷����� ������ ���������� ��������.

		string name_without_ext = fs::path(element).stem().string(); //���� ��ο��� ���� �̸��� (Ȯ����, ��Ÿ ��� ����)

		//���ڿ����� Ư�� ���ڸ� ã�´�, ã�� ���ڰ� ���� ���� string::npos�� �����Ѵ�. (������ ��)
		//ġȯ�� ã�� ���ڿ��� �����ϸ�
		if (name_without_ext.find(find) != string::npos) {

			//ReplaceAll�� ������ �����ϴ� Call By Reference �Լ����� ����

			string origin_path = element; //���� ��� ���
			string origin_without_ext = name_without_ext; //���� �̸� ���

			ReplaceAll(name_without_ext, find, replace); //�Ʊ� ���� name_without_ext�� �۾�
			ReplaceAll(element, origin_without_ext, name_without_ext); //������ �ݿ��ؼ� ��������. (file_list�� �������̶� �ݵ�� ������ �ݿ������ ��.)

			int status = rename(origin_path.c_str(), element.c_str());
			if (status == 0)
			{
				cout << format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
			}
			else if (status == -1)
			{
				cout << format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
				element = origin_path; //�۾� ���н� ���� ����Ʈ ��Ҹ� ������� �ǵ�����.
			}
		}
	}
}

void FileManager::insert_left_name(vector<string>& lst, string& insert_str)
{
	for (string& element : lst) { //element�� ���۷����� ������ ���������� ��������.

		string name_without_ext = fs::path(element).stem().string(); //���� ��ο��� ���� �̸��� (Ȯ����, ��Ÿ ��� ����)

		//ReplaceAll�� ������ �����ϴ� Call By Reference �Լ����� ����

		string origin_path = element; //���� ��� ���
		string origin_without_ext = name_without_ext; //���� �̸� ���

		name_without_ext = insert_str + name_without_ext; //�Ʊ� ���� name_without_ext�� �۾�
		ReplaceAll(element, origin_without_ext, name_without_ext); //������ �ݿ��ؼ� ��������.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
	}
}

void FileManager::insert_right_name(vector<string>& lst, string& insert_str)
{
	for (string& element : lst) { //element�� ���۷����� ������ ���������� ��������.

		string name_without_ext = fs::path(element).stem().string(); //���� ��ο��� ���� �̸��� (Ȯ����, ��Ÿ ��� ����)

		//ReplaceAll�� ������ �����ϴ� Call By Reference �Լ����� ����

		string origin_path = element; //���� ��� ���
		string origin_without_ext = name_without_ext; //���� �̸� ���

		name_without_ext += insert_str; //�Ʊ� ���� name_without_ext�� �۾�
		ReplaceAll(element, origin_without_ext, name_without_ext); //������ �ݿ��ؼ� ��������.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
	}
}


//��� ���� �������� ���ڸ� üũ�ϰ� ������ ��������. 
//���۷����� ������ �����Ѵ�.
void FileManager::insert_last_symbol(string& path)
{
	int length = path.length();
	//string �� �迭 ���ó�� ���ٽ� �ε��� ���ٽ� ���ϵǴ°� string�� �ƴ� char �ѹ������� ��������!! (��������ǥ ���)
	if (path[length-1] != '\\') { //���� �������÷� ������ ������
		path += "\\"; //���� �������ø� �ٿ��ش�. 
	}
}

//���ڿ� ġȯ �Լ� (Call by Value)
string FileManager::ReplaceAll(string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0; //stringó������ �˻�
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)  //from�� ã�� �� ���� ������
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // �ߺ��˻縦 ���ϰ� from.length() > to.length()�� ��츦 ���ؼ�
	}
	return str;
}