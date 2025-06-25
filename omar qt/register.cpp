#include"register.h"
#include"data.h"
Register::Register(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->welcome1_page);
}

Register::~Register()
{
    delete ui;
}



bool Register::SignInFun(const string& username, const string& userpass, bool& validpasskey)
{
    name = username;
    password = userpass;
    bool IsFound = false;
    for (int i = 0; i < number_of_users_in_array; i++) {
        qInfo() << arr_users[i].username << " <<  USERNAME  " << arr_users[i].pass;
        if (name == arr_users[i].username && password == arr_users[i].pass) {
            IsFound = true;
            indexofuser = i;
            current_user_id = arr_users[i].id;
            if (arr_users[i].admin_role) {
                const string passkey = "#ADMIN#2025";
                string trypasskey = passkey; // Qt: always trust it or use a dialog to get input
                if (trypasskey == passkey)
                    validpasskey = true;
            }
            break;
        }
    }
    return IsFound;
}

bool Register::newaccount(const string& username, const string& userpass, const string& email)
{
    for (int i = 0; i < number_of_users_in_array; i++) {
        if (arr_users[i].username == username || arr_users[i].contactdet.email == email)
            return false; // User exists
    }
    arr_users[number_of_users_in_array].username = username;
    arr_users[number_of_users_in_array].pass = userpass;
    arr_users[number_of_users_in_array].contactdet.email = email;
    arr_users[number_of_users_in_array].admin_role = false;
    arr_users[number_of_users_in_array].id = "ID" + to_string(number_of_users_in_array + 1); // simple ID
    indexofuser = number_of_users_in_array; 
    number_of_users_in_array++;
    return true;
}

void Register::on_create_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->signin_page);
}

void Register::on_login_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login_page);
}

void Register::on_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcome1_page);
}

void Register::on_back2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcome1_page);
}

void Register::on_pushButton_sign_clicked()
{
    QString username = ui->lineEdit_username_3->text().trimmed();
    QString password = ui->lineEdit_password_3->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString balance = ui->lineEdit_balance->text().trimmed();

    bool success = newaccount(username.toStdString(), password.toStdString(), email.toStdString());

    if (success) 
    {
        saveusersinfo();
        QMessageBox::information(this, "Sign Up", "Account created successfully!");
        emit switchToMainWindow();

        ///-------------------------///

    }
    else {
        QMessageBox::warning(this, "Sign Up", "Username or email already exists.");
    }
}

void Register::on_pushButton_login_clicked()
{
   
    QString username = ui->lineEdit_username_2->text().trimmed();
    QString password = ui->lineEdit_password_2->text().trimmed();
    QString admincheck = ui->lineEdit_admincheck_2->text().trimmed();

    bool validpasskey = false;
    if (admincheck == "#ADMIN#2025")
    {
        validpasskey = true;
    }

    bool success = SignInFun(username.toStdString(), password.toStdString(), validpasskey);

    if (success && admincheck=="") {
        QMessageBox::information(this, "Login", "Login Successful");
        emit switchToMainWindow();
    }
    else if (success && validpasskey)
    {
        QMessageBox::information(this, "Login", "Login Successful");
        emit windowadmin();
       
    }

    else {
        QMessageBox::warning(this, "Login", "Incorrect username or password");
    }
     ui->lineEdit_password_2->clear();
    ui->lineEdit_username_2->clear();



}

void Register::setPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index); 

}

