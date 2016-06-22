/**
 * @file deviceloader.hpp
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
#ifndef KOMIX_WIDGET_DEVICELOADER_HPP
#define KOMIX_WIDGET_DEVICELOADER_HPP

#include <QtCore/QIODevice>
#include <QtGui/QMovie>
#include <QtGui/QPixmap>

#include <memory>

namespace KomiX {
class DeviceLoader : public QObject {
    Q_OBJECT
public:
    DeviceLoader(int id, QIODevice * device);

    void start() const;

signals:
    void finished(int id, const QPixmap & pixmap);
    void finished(int id, QMovie * movie);

private:
    class Private;
    std::shared_ptr<Private> p_;
};
}

#endif
