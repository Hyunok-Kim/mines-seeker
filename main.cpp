#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QLocale>
#include <QVersionNumber>
#include <QFont>
#include <QFontDatabase>
#include <QTranslator>
#include <QLibraryInfo>
#include <QQuickView>
#include <QSplashScreen>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QLockFile>
#include <QIcon>

#include "generalsettings.h"
#include "startupprogress.h"
#include "arcade.h"
#include "cell.h"
#include "board.h"
#include "recordsmanager.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QLocale::setDefault(QLocale::English);


    QApplication app(argc, argv);
    app.setOrganizationName("TheCrowporation");
    app.setApplicationName("MinesSeeker");
    app.setApplicationVersion("1.0.1");
    app.setWindowIcon(QIcon(":/images/appIcon.png"));

    QSplashScreen splash(QPixmap(":/images/Logo512_BG.png").scaledToHeight(350, Qt::SmoothTransformation), Qt::WindowFlags() | Qt::WindowStaysOnTopHint);
    splash.show();
    app.processEvents();

    // SETTINGS
    GeneralSettings settings;

    // INTERNATIONALIZATION
    QTranslator qtTranslator;
    qtTranslator.load(QLocale(settings.getLanguage()), QStringLiteral("qt"), QStringLiteral("_"), ":/");
    app.installTranslator(&qtTranslator);

    QTranslator myAppTranslator;
    myAppTranslator.load(QLocale(settings.getLanguage()), QStringLiteral("mines"), QStringLiteral("_"), ":/");
    app.installTranslator(&myAppTranslator);

    // ALLOW JUST ONE RUNING INSTANCE
    QString lockFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + QString("/m%1.lock").arg(qApp->applicationVersion().replace('.', '_'));
    QLockFile lockFile(lockFilePath);
    if (!lockFile.tryLock()) {
        qCritical() << "lockFilePath = " << lockFilePath;
        QMessageBox::information(nullptr, QObject::tr("MinesSeeker"), QObject::tr("An instance of MinesSeeker is already running.\n"
                                                                                  "Close it in order to run a new one."));
        return 0;
    }

    // DATABASE PATH CHECKING
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir appDataDir(appDataPath);
    if (!appDataDir.exists()) {
        if (!appDataDir.mkpath(appDataPath)) {
            splash.close();
            QMessageBox::critical(nullptr, QObject::tr("MinesSeeker"), QObject::tr("Cannot create the folder:\n"
                                                                                   "%1.\n"
                                                                                   "Execute this application as root or create the folder manually.").arg(appDataPath));
            app.processEvents();
            return 1;
        }
    }

    // SPLASH
    QQuickView qv;
    qv.setFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    qv.setColor(Qt::transparent);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    qmlRegisterType<Cell>  ("Minesweeper", 1, 0, "Cell");
    qmlRegisterType<Board> ("Minesweeper", 1, 0, "Board");
    qmlRegisterType<Arcade>("Minesweeper", 1, 0, "Arcade");
    qmlRegisterUncreatableType<GeneralSettings>("Minesweeper", 1, 0, "GeneralSettings", "Cannot create object of this type.");
    settings.loadSettings();

    StartupProgress sp;
    qv.engine()->rootContext()->setContextProperty("startupManager", &sp);
    qv.setSource(QUrl(QStringLiteral("qrc:/mines-seeker/Loading.qml")));
    qv.show();

    QObject::connect( &sp, &StartupProgress::progressChanged, [&](double value) {
        qDebug() << "value = " << value;
        splash.showMessage(sp.getProgressMessage() + QString(" ...%1%").arg(value * 100.0, 0, 'f', 2), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
        app.processEvents();

    });
    QObject::connect( &sp, &StartupProgress::progressMessageChanged, [&](const QString &newMsg) {
        qDebug() << "newMsg = " << newMsg;
        QString msg = newMsg;
        double progress = sp.getProgress();
        if (progress > 0.0) {
            msg += QString(" ...%1%").arg(progress, 0, 'f', 2);
        }
        splash.showMessage(msg);
        app.processEvents();
    });

    QObject::connect( &sp, &StartupProgress::readyToLoadMainQMLFile, [&](){
        splash.close();
        app.processEvents();
        qDebug() << "Splash Done...";

        // FONTS
        sp.setProgressMessage(QObject::tr("Loading fonts..."));

        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Black.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-BlackIt.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Bold.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-ExtraLight.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-ExtraLightIt.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-It.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Light.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-LightIt.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Medium.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-MediumIt.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Regular.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-Semibold.otf");
        QFontDatabase::addApplicationFont(":/fonts/SourceCodePro/SourceCodePro-SemiboldIt.otf");

        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777B.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777Bb.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777BI.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777I.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777L.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777LI.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777Lt.ttf");
        QFontDatabase::addApplicationFont(":/fonts/HUMNST777/HUM777N.ttf");

        sp.setProgressMessage(QObject::tr("Loading scores..."));

        QString databaseFile = appDataPath + "/records.db";
        static RecordsManager recordManager(databaseFile);

        // QML_ENGINE
        sp.setProgressMessage(QObject::tr("Registering C++ types into QML engine..."));
        engine.rootContext()->setContextProperty("settings", &settings);
        engine.rootContext()->setContextProperty("recordManager", &recordManager);
        engine.rootContext()->setContextProperty("startupManager", &sp);

        QObject::connect(&settings, &GeneralSettings::languageChanged, [&](const QString &newLanguage) {
            QLocale::setDefault(QLocale(newLanguage));
            qtTranslator.load(QLocale(), QStringLiteral("qt"), QStringLiteral("_"), ":/");
            myAppTranslator.load(QLocale(), QStringLiteral("mines"), QStringLiteral("_"), ":/");
            engine.retranslate();
        });

        sp.setProgressMessage(QObject::tr("Loading UI..."));

        const QUrl url(u"qrc:/mines-seeker/Main.qml"_qs);
        engine.load(url);
        if (engine.rootObjects().isEmpty()) {
            QGuiApplication::exit(-1);
        } else {
            qv.close();
            qv.engine()->deleteLater();
        }
    });

    int result = app.exec();
    lockFile.unlock();
    return result;
}

