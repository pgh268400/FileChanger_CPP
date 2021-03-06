#include <iostream>
#include "FileManager.h"
#include <filesystem>
#include <string>
#include "NatSort.hpp"


namespace fs = std::filesystem;


//경로를 입력받아서 초기화 하는 생성자 함수
FileManager::FileManager(string path)
{
	class unexpected_error{};
	//역슬래시 체크해서 삽입
	insert_last_symbol(path);

	//생성자 초기화
	dir_path = path;


	for (const auto& entry : fs::directory_iterator(path))
	{
		std::error_code error_code; //예외를 처리하지 않고 error_code에 저장함.
		bool isFile = fs::is_regular_file(entry.path(), error_code);

		string path = entry.path().string();
		if (isFile) { //파일인경우
			file_list.push_back(path);
		}
		else { //디렉토리인 경우
			dir_list.push_back(path);
		}
	}

	file_count = file_list.size();
	dir_count = dir_list.size();
	all_count = file_count + dir_count;

	//Natural Sort 알고리즘으로 친절하게 정렬도 수행 (Option)
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
	for (string& element : lst) { //element는 레퍼런스로 원본에 접근중임을 유의하자.

		string name_without_ext = fs::path(element).stem().string(); //원본 경로에서 오직 이름만 (확장자, 기타 경로 제거)

		//문자열에서 특정 문자를 찾는다, 찾는 문자가 없을 경우는 string::npos를 리턴한다. (쓰레기 값)
		//치환할 찾는 문자열이 존재하면
		if (name_without_ext.find(find) != string::npos) {

			//ReplaceAll은 원본을 변경하는 Call By Reference 함수임을 유의

			string origin_path = element; //원본 경로 백업
			string origin_without_ext = name_without_ext; //원본 이름 백업

			ReplaceAll(name_without_ext, find, replace); //아까 얻은 name_without_ext에 작업
			ReplaceAll(element, origin_without_ext, name_without_ext); //원본에 반영해서 수정해줌. (file_list로 관리중이라 반드시 원본에 반영해줘야 함.)

			int status = rename(origin_path.c_str(), element.c_str());
			if (status == 0)
			{
				cout << format(">>> {} 를 {} 로 변경하였습니다.", origin_path, element) << endl;
			}
			else if (status == -1)
			{
				cout << format(">>> {} 를 {} 로 변경하는데 실패하였습니다.", origin_path, element) << endl;
				element = origin_path; //작업 실패시 원본 리스트 요소를 원래대로 되돌린다.
			}
		}
	}
}

void FileManager::insert_left_name(vector<string>& lst, string& insert_str)
{
	for (string& element : lst) { //element는 레퍼런스로 원본에 접근중임을 유의하자.

		string name_without_ext = fs::path(element).stem().string(); //원본 경로에서 오직 이름만 (확장자, 기타 경로 제거)

		//ReplaceAll은 원본을 변경하는 Call By Reference 함수임을 유의

		string origin_path = element; //원본 경로 백업
		string origin_without_ext = name_without_ext; //원본 이름 백업

		name_without_ext = insert_str + name_without_ext; //아까 얻은 name_without_ext에 작업
		ReplaceAll(element, origin_without_ext, name_without_ext); //원본에 반영해서 수정해줌.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << format(">>> {} 를 {} 로 변경하였습니다.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << format(">>> {} 를 {} 로 변경하는데 실패하였습니다.", origin_path, element) << endl;
		}
	}
}

void FileManager::insert_right_name(vector<string>& lst, string& insert_str)
{
	for (string& element : lst) { //element는 레퍼런스로 원본에 접근중임을 유의하자.

		string name_without_ext = fs::path(element).stem().string(); //원본 경로에서 오직 이름만 (확장자, 기타 경로 제거)

		//ReplaceAll은 원본을 변경하는 Call By Reference 함수임을 유의

		string origin_path = element; //원본 경로 백업
		string origin_without_ext = name_without_ext; //원본 이름 백업

		name_without_ext += insert_str; //아까 얻은 name_without_ext에 작업
		ReplaceAll(element, origin_without_ext, name_without_ext); //원본에 반영해서 수정해줌.

		int status = rename(origin_path.c_str(), element.c_str());
		if (status == 0)
		{
			cout << format(">>> {} 를 {} 로 변경하였습니다.", origin_path, element) << endl;
		}
		else if (status == -1)
		{
			cout << format(">>> {} 를 {} 로 변경하는데 실패하였습니다.", origin_path, element) << endl;
		}
	}
}


//경로 끝에 역슬래시 문자를 체크하고 없으면 삽입해줌. 
//레퍼런스로 원본을 변경한다.
void FileManager::insert_last_symbol(string& path)
{
	int length = path.length();
	//string 을 배열 요소처럼 접근시 인덱스 접근시 리턴되는건 string이 아닌 char 한문자임을 유의하자!! (작은따옴표 사용)
	if (path[length-1] != '\\') { //끝이 역슬래시로 끝나지 않으면
		path += "\\"; //끝에 역슬래시를 붙여준다. 
	}
}

//문자열 치환 함수 (Call by Value)
string FileManager::ReplaceAll(string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0; //string처음부터 검사
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)  //from을 찾을 수 없을 때까지
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
	}
	return str;
}