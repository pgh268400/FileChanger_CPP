#include <iostream>
#include <string>
#include "FileManager.h"
#include <format>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::format;


//아스키 아트 출력용 변수
string ascii_art = "______  _  _         _____  _                                      \n|  ___|(_)| |       /  __ \\| |                                     \n| |_    _ | |  ___  | /  \\/| |__    __ _  _ __    __ _   ___  _ __ \n|  _|  | || | / _ \\ | |    | '_ \\  / _` || '_ \\  / _` | / _ \\| '__|\n| |    | || ||  __/ | \\__/\\| | | || (_| || | | || (_| ||  __/| |   \n\\_|    |_||_| \\___|  \\____/|_| |_| \\__,_||_| |_| \\__, | \\___||_|   \n                                                  __/ |            \n                                                 |___/\n";


void draw_border() {
	cout << "--------------------------------------------------------------------\n";
}

void draw_main()
{
	//첫 시작화면 렌더링 
	draw_border();
	cout << ascii_art;
	cout << "간편 파일이름 변경기 v0.1" << endl;
	draw_border();
}



string get_file_path(string dialog)
{
	//경로 입력 저장용 임시 변수
	string temp;

	//입력 다이얼로그 출력
	cout << dialog;

	//cin 으로 받으면 공백까지 입력 받을 수 없다. getline 을 쓰면 공백을 포함해서 읽어줌.
	std::getline(cin, temp);

	draw_border();

	return temp;
}

int main(void) {
	setlocale(LC_ALL, ""); //한글 경로 읽기 위해 로케일을 해당 컴퓨터에 있는 로케일로 바꾼다. (필수)

	string dir_path = "";

	//첫 시작화면 렌더링 
	draw_main();

	//경로 입력 받기
	dir_path = get_file_path("폴더 경로를 입력해주세요. : ");

	//파일을 다루기 위해 FileManager 객체 생성하기
	FileManager fm(dir_path); //객체 생성

	if (fm.get_file_count() != 0) {
		fm.print_file_list(); //파일 리스트 출력
	}
	else {
		cout << "No Files in Directory...";
		return 0;
	}

	draw_border();

	string mode;

	do {
		cout << "작업하실 모드를 선택해주세요 (p : 치환모드, l : 왼쪽에 문자열 삽입, r : 오른쪽에 문자열 삽입, e : 종료) : ";
		cin >> mode;
		cin.ignore(); //문자 한개만큼 입력버퍼 비우기


		if (mode == "p") {
			string find, replace;
			cout << "찾을 문자열을 입력해주세요 : ";
			getline(cin, find);

			cout << "치환할 문자열을 입력해주세요 : ";
			getline(cin, replace);

			string dialog;
			cout << format("해당 경로의 \"{}\" 문자를 찾아서 \"{}\" (으)로 치환해서 이름을 변경합니다. \n정말 수행하시겠습니까 ? (y/n) : ", find, replace);
			cin >> dialog;

			if (dialog == "y") {
				fm.replace_file_name(find, replace);
			}
			else {
				printf("사용자에 의해 작업이 취소되었습니다.\n");
			}
		}
		else if (mode == "e") {
			cout << "사용자에 의해 작업이 종료되었습니다.";
		}
		else if (mode == "l") {
			string insert_str, dialog;
			cout << "삽입할 문자열을 입력해주세요 : ";
			getline(cin, insert_str);

			cout << format("해당 경로의 파일 이름 앞에 \"{}\" 을 모두 삽입합니다. \n정말 수행하시겠습니까 ? (y/n) : ", insert_str);
			cin >> dialog;

			if (dialog == "y") {
				fm.insert_left_file_name(insert_str);
			}
			else {
				printf("사용자에 의해 작업이 취소되었습니다.\n");
			}
		}
		else if (mode == "r") {
			string insert_str, dialog;
			cout << "삽입할 문자열을 입력해주세요 : ";
			getline(cin, insert_str);

			cout << format("해당 경로의 파일 이름 뒤에 \"{}\" 을 모두 삽입합니다. \n정말 수행하시겠습니까 ? (y/n) : ", insert_str);
			cin >> dialog;

			if (dialog == "y") {
				fm.insert_right_file_name(insert_str);
			}
			else {
				printf("사용자에 의해 작업이 취소되었습니다.\n");
			}
		}
		else {
			printf("올바른 모드가 아닙니다.");
		}
	} while (mode != "e");

	getchar(); //프로그램 바로 종료되지 않게 하기
	return 0;
}