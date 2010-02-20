/**
 * @file mainwindow.hpp
 * @author Wei-Cheng Pan
 *
 * KomiX, a comics viewer.
 * Copyright (C) 2008  Wei-Cheng Pan <legnaleurc@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KOMIX_WIDGET_MAINWINDOW_HPP
#define KOMIX_WIDGET_MAINWINDOW_HPP

#include <QtGui/QMainWindow>
#include <QtGui/QSystemTrayIcon>

namespace Ui {
	class MainWindow;
}
class QSystemTrayIcon;
class QUrl;

namespace KomiX {
	namespace widget {

		class AboutWidget;
		class ImageArea;
		class Preference;

		/**
		 * @brief Main window
		 *
		 * The main window widget, all GUI components are managed by this.
		 */
		class MainWindow : public QMainWindow {
			Q_OBJECT

		public:
			/**
			 * @brief default constructor
			 * @param parent parent widget
			 * @param f window flags
			 */
			explicit MainWindow( QWidget * parent = 0, Qt::WindowFlags f = 0 );
			virtual ~MainWindow();

		public slots:
			/**
			 * @brief open url
			 * @param url file url
			 */
			void open( const QUrl & url );
			void open( const QString & localFile );
			/// toggle full-screen mode
			void toggleFullScreen();
			/// toggle minimize system tray
			void toggleSystemTray();

		private slots:
			void systemTrayHelper_( QSystemTrayIcon::ActivationReason reason );
			void popupError_( const QString & errMsg );

		private:
			void setupMenuBar_();
			void setupFileMenu_();
			void setupEditMenu_();
			void setupViewMenu_();
			void setupGoMenu_();
			void setupHelpMenu_();
			void initCentralWidget_();
			void initTrayIcon_();

			Ui::MainWindow * ui_;
			ImageArea * imageArea_;
			Preference * preference_;
			QSystemTrayIcon * trayIcon_;
			AboutWidget * about_;
			Qt::WindowStates dumpState_;
		};
	
	}
} // end namespace

#endif
