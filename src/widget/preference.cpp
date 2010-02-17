/**
 * @file preference.cpp
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

#include "preference.hpp"

#include <QtCore/QSettings>

using namespace KomiX::widget;

Preference::Preference( QWidget * parent ):
QDialog( parent ),
ui_() {
	this->ui_.setupUi( this );

	connect( this->ui_.buttons, SIGNAL( clicked( QAbstractButton * ) ), this, SLOT( dispatch_( QAbstractButton * ) ) );

	this->ui_.language->addItem( "English (United States)", "en_US" );
	this->ui_.language->addItem( "\xE6\xAD\xA3\xE9\xAB\x94\xE4\xB8\xAD\xE6\x96\x87", "zh_TW" );
	this->ui_.language->addItem( "\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E", "ja_JP" );
}

void Preference::changeEvent( QEvent * event ) {
	if( event->type() == QEvent::LanguageChange ) {
		this->ui_.retranslateUi( this );
	} else {
		this->QDialog::changeEvent( event );
	}
}

void Preference::dispatch_( QAbstractButton * button ) {
	switch( this->ui_.buttons->buttonRole( button ) ) {
	case QDialogButtonBox::RejectRole:
		this->reject();
		break;
	case QDialogButtonBox::ApplyRole:
		this->accept();
		break;
	case QDialogButtonBox::AcceptRole:
		this->accept();
		this->hide();
		break;
	default:
		;
	}
}

void Preference::load() {
	QSettings ini;

	QVariant value = ini.value( "language", "en_US" );
	int index = this->ui_.language->findData( value );
	if( index < 0 ) {
		this->ui_.language->setCurrentIndex( 0 );
	} else {
		this->ui_.language->setCurrentIndex( index );
	}
	emit languageChanged( this->ui_.language->itemData( this->ui_.language->currentIndex() ).toString() );

	this->ui_.pixelInterval->setValue( ini.value( "pixel_interval", 1 ).toInt() );
	this->ui_.timeInterval->setValue( ini.value( "time_interval", 1 ).toInt() );
}

void Preference::saveSettings_() {
	QSettings ini;

	QVariant language = this->ui_.language->itemData( this->ui_.language->currentIndex() );
	ini.setValue( "language", language );
	emit languageChanged( language.toString() );

	ini.setValue( "pixel_interval", this->ui_.pixelInterval->value() );
	ini.setValue( "time_interval", this->ui_.timeInterval->value() );
}

void Preference::accept() {
	this->saveSettings_();

	emit accepted();
}

void Preference::reject() {
	this->load();

	QDialog::reject();
}
