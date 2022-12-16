#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
using namespace std;

// /======TAO HAM GOTOXY====
// /======UPDATE SẼ NHÉC VÀO FILE HEADER
void gotoxy(int x, int y)
{
    COORD khoalatao;
    khoalatao.X = x;
    khoalatao.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), khoalatao);
}

// / === HÀM ĐỔI MÀU CHỮ=====
void textcolor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

struct sinh_vien
{
    string khoa_hoc;
    int id;
    string ten;
    string gioi_tinh;
    string date;
};

typedef struct sinh_vien SV;

// =====Khai báo biến cục bộ

//--số sinh viên thêm---
int n;
//--vector danh sách sinh viên thuộc struct SV
vector<SV> ds;

//-vector chứa id----
vector<int> id;
//--kết quả trong menu---
int cn = 1;

//-- biến thoát menu---
bool kt = true;

//---lưu tạm id -------
int fixid;

//====Lưu khóa học+++
vector<string>khoalatao;




//===== Nạp chồng toán tử >> Nhập vào
istream &operator>>(istream &is, SV &ds)
{
    fflush(stdin);
    cout << "Nhap khoa hoc: ";
    getline(is, ds.khoa_hoc);

    // id sinh viên sẽ được bằng hàm

    fflush(stdin);
    cout << "Nhap ten sinh vien: ";
    getline(is, ds.ten);

    fflush(stdin);
    cout << "Nhap gioi tinh: ";
    is >> ds.gioi_tinh;

    fflush(stdin);
    cout << "Nhap ngay thang nam sinh (xx/yy/zzzz): ";
    getline(is, ds.date);

    return is;
}



// =====Nạp chồng toán tử << xuất ra
ostream &operator<<(ostream &os, SV &ds)
{
    os << "Khoa hoc: " << ds.khoa_hoc << endl;
    os << "Ma so sinh vien: " << ds.id << endl;
    os << "Ten sinh vien: " << ds.ten << endl;
    os << "Gioi tinh: " << ds.gioi_tinh << endl;
    os << "Ngay sinh: " << ds.date << endl;
    return os;
}



// =====tạo đường kẻ
void create_line(int size)
{
    for (int i = 0; i < size; i++)
    {
        cout <<char(196)<<char(196);
    }
    cout << endl;
}

//=====TẠO ID SINH VIÊN
void create_id(int begin, int end);

//======IN FILE "danhsachSV.txt"
void printfFile();

/// ==== ĐỌC FIE GHI VÀO VECTOR DS
void loadFile();


//===in file===========
void printfFile()
{
    fstream file;
    file.open("danhsachSV.txt", ios_base::out);
    for (int i = 0; i < ds.size(); i++)
    {
        if(i<ds.size()) file << endl;
        file << ds[i].id << "," << ds[i].khoa_hoc << "," << ds[i].ten << "," << ds[i].gioi_tinh << "," << ds[i].date;
    }

    file.close();
}
void loadFile()
{
    fstream lfile;
    lfile.open("danhsachSV.txt", ios_base::in);
    while (!lfile.eof())
    {
        SV a;
        lfile >> a.id;
        lfile.ignore();
        getline(lfile, a.khoa_hoc, ',');
        getline(lfile, a.ten, ',');
        getline(lfile, a.gioi_tinh, ',');
        getline(lfile, a.date); // lấy string, nếu đây là int thì ffile ra để xuống dòng tạo thêm hàm ignore
        // lfile.ignore();
        ds.push_back(a);
    }
    lfile.close();
}


//=====in chữ huỳnh anh khoa chóp chóp===
void khoa();

//=====menu động lỏ như sa ngộ tị===
void menuv2();

///====Vẽ con trỏ lựa chọn trong menu====
void contro(int cn);

//=====Tự động cấp mã sinh viên random không trùng !!!===
int set_idSV();


//=====tìm kiếm ds theo id===//cho id nhận đc vị trí===
int search(int key);


//======Sắp sếp ds sinh viên nhưng không lưu====
void Sort();

//===========Duyệt lại vetor id
void browserV(vector<int> v);

//==========Chỉnh sửa thông tin sinh viên-------
void updateSV(int key);
//=========Tìm kiếm sinh viên theo khóa học======
void search_string(string a);

//=====Duyệt và lưu lại khóa học không trùng+++
void doc_khoa();

//====menu cho chức năng số 7==========
void menu_sp7(int x);
void ct_so_7();

void khoa()
{
    system("cls");
    for (int i = 0; i < 16; i++)
    {
        gotoxy(5, 0);
        cout << "              ";
        textcolor(i);
        cout << "Huynh Anh Khoa";
        Sleep(50);
    }
}

void menuv2()
{
    system("cls");
    textcolor(10);
    cout << "\n\n\t\tCHUONG TRINH QUAN LY SINH VIEN" << endl;
    gotoxy(6, 4);
    cout << "1. Hien thi danh sach sinh vien";
    gotoxy(6, 5);
    cout << "2. Nhap sinh vien";
    gotoxy(6, 6);
    cout << "3. Tim kiem sinh vien";
    gotoxy(6, 7);
    cout << "4. Sap xep sinh vien theo id";
    gotoxy(6, 8);
    cout<<"5. Xoa sinh vien theo id";
    gotoxy(6, 9);
    cout<<"6. Cap nhat thong tin sinh vien";
    gotoxy(6, 10);
    cout<<"7. Hien danh sach sinh vien theo khoa hoc";
    gotoxy(6,11);
    cout<<"8. Thoat";
    contro(cn);
    int t = getch();
    if (t == 13)
    {
        switch (cn)
        {
        case 1:
        {
            system("cls");
            textcolor(7);
            cout << "\n\t\tCHUONG TRINH QUAN LY SINH VIEN" << endl;
            create_line(30);
            if (ds.size() < 1)
                cout << "Khong co sinh vien!" << endl;
            else
                cout << "\n\tSo luong sinh vien: " << ds.size() << endl;
            create_line(30);
            if (ds.size() > 0)
                for (int i = 0; i < ds.size(); i++)
                {
                    textcolor(14);
                    cout << ds[i] << endl;
                    textcolor(7);
                    create_line(30);
                }
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            cout<<"\n\tTHEM SINH VIEN"<<endl;
            textcolor(10);
            cout << "Nhap so luong sinh vien: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                if (i != 0)
                    create_line(50);
                SV a;
                cin >> a;
                a.id = set_idSV();
                ds.push_back(a);
            }
            printfFile();
            system("cls");
            cout<<"\tSinh vien da nhap: "<<endl;
            textcolor(10);
            create_line(30);
            cout<<ds.back();
            system("pause");
            break;
        }
        case 3:
        {
            system("cls");
            int haha;
            textcolor(6);
            cout<<"\n\tTIM KIEM SINH VIEN"<<endl;
            create_line(30);
            cout<<"Nhap ma so sinh vien: ";
            cin>>haha;
            if(search(haha)==-1){
                create_line(30);
                cout<<"Khong co sinh vien!"<<endl;
            }
            else{
                create_line(30);
                cout<<ds[search(haha)];
            }
            system("pause");
            break;
        }
        case 4:
        {
            system("cls");
            cout<<"\n\tSAP XEP SINH VIEN THEO ID"<<endl;
            create_line(30);
            Sort();
            textcolor(11);
            for(int i =0; i< ds.size(); i++)
            {
                if(i!=ds.size()) create_line(30);
                cout<<ds[i];
            }
            system("pause");
            break;
        }
        case 5:
        {
            system("cls");
            cout<<"\n\tXOA SINH VIEN THEO ID"<<endl;
            int c;
            cout<<"Nhap id sinh vien can xoa: ";
            cin>>c;
            create_line(30);
            textcolor(11);
            if(search(c)==-1) 
            {
                cout<<"Sinh vien khong ton tai!"<<endl;
                system("pause");
            }else
            {
                cout<<ds[search(c)];
                int kq;
                textcolor(4);
                cout<<"1.XOA\t\t2.THOAT"<<endl<<endl;
                cin>>kq;
                if(kq==1){
                    ds.erase(ds.begin()+search(c));
                    system("cls");
                    cout<<"\tDA XOA!"<<endl;
                    printfFile();
                    system("pause");
                }else{
                    break;
                }

            }
            break;
        }
        case 6:
        {
            system("cls");
            cout<<"\n\tCAP NHAT THONG TIN SINH VIEN"<<endl;
            int a;
            cout<<"Nhap id sinh vien: ";
            cin>>a;
            updateSV(a);
            printfFile();
            break;
        }
        case 7:
        {
            //còn lỗi khi xóa sinh viên chưa cập nhật khóa, chờ update nâng cấp
          ct_so_7();
          break;
        }
        case 8:
        {
            kt = false;
            break;
        }
        }
    }
    if (t == 80)
    {
        cn++;
        contro(cn);
    }
    if (t == 72)
    {
        cn--;
        contro(cn);
    }
    if (cn > 8)
        cn = 1;
    if (cn < 1)
        cn = 8;
}

void contro(int cn)
{
    int n = cn + 4;
    for (int i = 0; i < n; i++)
    {
        gotoxy(4, i - 1);
        cout << " ";
        gotoxy(4, i);
        textcolor(4);
        cout << char(16);
    }
    gotoxy(0, 10);
}

//========Set id cho sinh viên==========
void create_id(int begin, int end)
{
    for (int i = begin; i < end; i++)
    {
        id.push_back(i);
    }
}

int set_idSV()
{
    int tam = id.back();
    id.pop_back();
    return tam;
}

void browserV(vector<int> v)
{
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << endl;
}


//=======NÂNG CẤP SET ID CHO SINH VIÊN ==========
//=======kiểm tra trung=================
int update_setid()
{
    fixid = ds.back().id;
    for(int i =0; i< id.size(); i++)
    {
        if(id[i]==fixid) return i;
    }
    return -1;
}
///=============Tìm kiếm sinh viên ==========
int search(int key)
{
    for(int i =0; i< ds.size(); i++)
    {
        if(key==ds[i].id) return i;

    }
    return -1;
}

///==========UPDATE NÂNG CẤP HÀM TẠO ID==========


//===trộn vector id======
void swap_ngu()
{
    int k = 0, n = id.size()-1;
    srand(time(NULL));
    while (k <= n)
    {
        int a = rand()%(n - 0 + 1) + 0;
        swap(id[k], id[a]);
        k++;
    }
}

//====kiểm tra id đã sử dụng chưa===
int kt_trung(int key)
{
    for(int i =0; i < id.size(); i++)
    {
        if(key==id[i]) return i;
    }
    return -1;
}


//------xóa các id đã được cấp---------
void xoa_trung()
{
    vector<int>ngu;
    for(int i =0; i< ds.size(); i++)
    {
        ngu.push_back(ds[i].id);
    }
    for(auto x:ngu)
    {
        if(kt_trung(x)==-1){
            continue;
        }
        else{
            id.erase(id.begin()+kt_trung(x));
        }
    }
}


///===========Sắp sếp sinh viên theo id=============
///===========CHƯA UPDATE THUẬT TOÁN ===============
void Sort()
{
    for(int i =0; i < ds.size(); i++)
    {
        for(int j = i+1; j<ds.size(); j++)
        {
            if(ds[i].id>ds[j].id) swap(ds[i], ds[j]);
        }
    }
}



///===========CHỈNH CHỬA THÔNG TIN SINH VIÊN=======
void updateSV(int key)
{   
    int a = search(key);
    if(a == -1)
    {
        cout<<"Sinh vien khong ton tai!"<<endl;
        system("pause");
    }else
    {
        create_line(30);
        cout<<ds[a];
        cout<<"Chinh sua: "<<endl;
        cin>>ds[a];
        cout<<"Da cap nhat sinh vien"<<endl;
        system("pause");
    }
}   




//==========Tìm kiếm sinh viên theo khóa học=====
void search_string(string a)
{
    system("cls");
    cout<<"\n\tDanh sach sinh vien khoa: ";
    textcolor(12);
    cout<<a<<endl;
    textcolor(7);
    cout<<"\t\tcho update"<<endl;
    create_line(30);
    for(int i =0; i< ds.size(); i++)
    {
        if(ds[i].khoa_hoc==a)
        {
            textcolor(3);
            cout<<ds[i];
            textcolor(7);
            create_line(30);
        }
    }
}




bool kt_khoalatao(string a)
{
    for(auto x: khoalatao)
    {
        if(x == a) return true;
    }
    return false;
}
void doc_khoa()
{
    // khoalatao.push_back(ds[0].khoa_hoc);
    for(int i = 0; i < ds.size(); i++)
    {
        if(kt_khoalatao(ds[i].khoa_hoc) == false) khoalatao.push_back(ds[i].khoa_hoc);
    }
}

void menu_sp7(int x)
{
    system("cls");
    textcolor(14);
    cout<<"\tCHON KHOA HOC"<<endl;
    create_line(30);
    for(int i =0; i< khoalatao.size(); i ++)
    {
        textcolor(7);
        if(i==x) textcolor(4);
        gotoxy(6, i+2);
        cout<<khoalatao[i];
    }
}
void ct_so_7()
{
    int a =0;
    bool khoadeongu = true;
    while(khoadeongu)
    {
        menu_sp7(a);
        int anphim = getch();
        if(anphim == 13) 
        {
           search_string(khoalatao[a]);
           system("pause");
           khoadeongu = false;
        }
        if(anphim == 80)
        {
            a++;
            if(a >= khoalatao.size()) a = 0;
            menu_sp7(a);
        }
        if(anphim == 72)
        {
            a--;
            if(a < 0) a = khoalatao.size() - 1;
            menu_sp7(a);
        }
    }   
}


////---chạy code lỏ-------


int main()
{
    
    // loadFile();
    // doc_khoa();
    // ct_so_7();
    create_id(10000, 19999); //Tạo id trong khoảng; sẽ update sịn lại
    loadFile();//load file "danhsachSV.txt"
    swap_ngu();//trộn id + kết hợp với hàm tạo id create_id
    xoa_trung();//xóa id trùng
    doc_khoa();
    khoa();
    while (kt)
    {
        menuv2();
    }
    return 0;
}
