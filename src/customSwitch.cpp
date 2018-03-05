/*
 * Copyright 2017 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "customSwitch.hpp"

#include <QDebug>
#include <QResizeEvent>

using namespace adiscope;

CustomSwitch::CustomSwitch(QWidget *parent) : QPushButton(parent),
	on(this), off(this), handle(this), anim(&handle, "geometry")
{
	on.setObjectName("on");
	off.setObjectName("off");
	handle.setObjectName("handle");

	setFlat(true);
	setCheckable(true);
	setDuration(100);

	QFile file(":stylesheets/stylesheets/customSwitch.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QString::fromLatin1(file.readAll());
	this->setStyleSheet(styleSheet);

	connect(this, SIGNAL(toggled(bool)), SLOT(toggleAnim(bool)));
	on.raise();
	off.raise();
	on.setText("on");
	off.setText("off");
	updateOnOffLabels();
}

void CustomSwitch::updateOnOffLabels()
{
	on.setEnabled(isChecked());
	off.setEnabled(!isChecked());
}

bool CustomSwitch::event(QEvent *e)
{
	if (e->type() == QEvent::DynamicPropertyChange)
	{
		QDynamicPropertyChangeEvent *const propEvent = static_cast<QDynamicPropertyChangeEvent*>(e);
		QString propName = propEvent->propertyName();
		if(propName=="leftText" && property("leftText").isValid())
			on.setText(property("leftText").toString());
		if(propName=="rightText" && property("rightText").isValid())
			off.setText(property("rightText").toString());

	}
	return QPushButton::event(e);
}

CustomSwitch::~CustomSwitch()
{
}

void CustomSwitch::setDuration(int ms)
{
	duration_ms = ms;
	anim.setDuration(ms);
}

void CustomSwitch::toggleAnim(bool enabled)
{
	if (!isVisible())
		return;

	QRect on_rect(0, handle.y(), handle.width(), handle.height());
	QRect off_rect(width() - handle.width(), handle.y(),
			handle.width(), handle.height());

	anim.stop();

	if (enabled) {
		anim.setStartValue(off_rect);
		anim.setEndValue(on_rect);
	} else {
		anim.setStartValue(on_rect);
		anim.setEndValue(off_rect);
	}

	updateOnOffLabels();
	anim.start();
}

void CustomSwitch::showEvent(QShowEvent *event)
{
	updateOnOffLabels();
	if (isChecked()) {
		handle.setGeometry(QRect(0, handle.y(), handle.width(),
					 handle.height()));
	}
	else {
		handle.setGeometry(QRect(width() - handle.width(), handle.y(),
					handle.width(), handle.height()));
	}

}
