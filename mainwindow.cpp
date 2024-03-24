#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webView = new QWebEngineView(this);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QString htmlCode = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Кошачья тема</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    margin: 0;
                    padding: 0;
                    background-color: #f0f0f0;
                }
                header {
                    background-color: #333;
                    color: #fff;
                    padding: 20px;
                    text-align: center;
                }
                nav {
                    background-color: #444;
                    color: #fff;
                    padding: 10px;
                    text-align: center;
                }
                nav a {
                    color: #fff;
                    text-decoration: none;
                    margin: 0 10px;
                }
                section {
                    padding: 20px;
                    text-align: center;
                }
                footer {
                    background-color: #333;
                    color: #fff;
                    text-align: center;
                    padding: 10px;
                    position: fixed;
                    bottom: 0;
                    width: 100%;
                }
            </style>
        </head>
        <body>
            <header>
                <h1>Милые котики</h1>
            </header>
            <nav>
                <a href="#">Главная</a>
                <a href="#">Фотогалерея</a>
                <a href="#">Контакты</a>
            </nav>
            <section>
                <h2>Добро пожаловать в мир милых котиков!</h2>
                <img src="https://kartinki.pics/uploads/posts/2022-12/1670031672_kartinkin-net-p-khoba-koshka-instagram-49.jpg" alt="Хоба" style="width:70%;">
                <p>На этом сайте вы найдете самые милые фотографии котиков.</p>
            </section>
            <footer>
                <p>© 2024 Милые котики. Все права защищены.</p>
            </footer>
        </body>
        </html>
    )";

    ui->plainTextEdit->setPlainText(htmlCode);
    updateWebView();

    QPlainTextEdit *plainTextEdit = ui->plainTextEdit;
    QHBoxLayout *horizontalLayout = dynamic_cast<QHBoxLayout*>(ui->horizontalLayout->layout());

    if (plainTextEdit && horizontalLayout) {
        horizontalLayout->addWidget(webView);
        connect(plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::updateWebView);
    } else {
        qDebug() << "Ошибка: plainTextEdit или horizontalLayout не найдены.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWebView()
{
    QString htmlCode = ui->plainTextEdit->toPlainText();

    QRegularExpression titleRegex("<title>(.*?)</title>");
    QRegularExpressionMatch match = titleRegex.match(htmlCode);
    if (match.hasMatch()) {
        QString title = match.captured(1);
        setWindowTitle(title);
    } else {
        setWindowTitle("MainWindow");
    }

    webView->setHtml(htmlCode);
}
