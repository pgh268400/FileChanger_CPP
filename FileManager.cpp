#include <iostream>
#include "FileManager.h"
#include <filesystem>
#include <string>


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
}

int FileManager::get_file_count() const { return file_count; }

void FileManager::print_file_list()
{
	for (string& element : file_list) {
		cout << element << endl;
	}
}

void FileManager::replace_file_name(string find, string replace)
{
	for (string& element : file_list) { //element�� ���۷����� ������ ���������� ��������.

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
				cout << std::format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
			}
			else if (status == -1)
			{
				cout << std::format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
				element = origin_path; //�۾� ���н� ���� ����Ʈ ��Ҹ� ������� �ǵ�����.
			}
		}
	}
}



//���� �̸� �����ʿ� ���ڿ� ����
void FileManager::insert_right_file_name(string insert_str)
{
	for (string& element : file_list) { //element�� ���۷����� ������ ���������� ��������.

		string name_without_ext = fs::path(element).stem().string(); //���� ��ο��� ���� �̸��� (Ȯ����, ��Ÿ ��� ����)

		//ReplaceAll�� ������ �����ϴ� Call By Reference �Լ����� ����

		string origin_path = element; //���� ��� ���
		string origin_without_ext = name_without_ext; //���� �̸� ���

		name_without_ext += insert_str; //�Ʊ� ���� name_without_ext�� �۾�
		ReplaceAll(element, origin_without_ext, name_without_ext); //������ �ݿ��ؼ� ��������.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << std::format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << std::format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
	}
}

//���� �̸� ���ʿ� ���ڿ� ����
void FileManager::insert_left_file_name(string insert_str)
{
	for (string& element : file_list) { //element�� ���۷����� ������ ���������� ��������.

		string name_without_ext = fs::path(element).stem().string(); //���� ��ο��� ���� �̸��� (Ȯ����, ��Ÿ ��� ����)

		//ReplaceAll�� ������ �����ϴ� Call By Reference �Լ����� ����

		string origin_path = element; //���� ��� ���
		string origin_without_ext = name_without_ext; //���� �̸� ���

		name_without_ext = insert_str + name_without_ext; //�Ʊ� ���� name_without_ext�� �۾�
		ReplaceAll(element, origin_without_ext, name_without_ext); //������ �ݿ��ؼ� ��������.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << std::format(">>> {} �� {} �� �����Ͽ����ϴ�.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << std::format(">>> {} �� {} �� �����ϴµ� �����Ͽ����ϴ�.", origin_path, element) << endl;
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