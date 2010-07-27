//
//   File : optw_taskbar.cpp
//   Creation date : Wed Jan 16 04:30:39 2002 GMT by Szymon Stefanek
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2001 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//

#include "optw_taskbar.h"

#include "kvi_settings.h"
#include "kvi_locale.h"
#include "kvi_options.h"


KviTaskBarOptionsWidget::KviTaskBarOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"taskbar_options_widget")
{

	createLayout(7,1);

	addBoolSelector(0,0,0,0,__tr2qs_ctx("Use tree taskbar","options"),KviOption_boolUseTreeWindowListTaskBar);
	addBoolSelector(0,1,0,1,__tr2qs_ctx("Sort windows by name","options"),KviOption_boolSortTaskBarItemsByName);
	addBoolSelector(0,2,0,2,__tr2qs_ctx("Show window icons in taskbar","options"),KviOption_boolUseTaskBarIcons);
	KviBoolSelector * b = addBoolSelector(0,3,0,3,__tr2qs_ctx("Show activity meter in taskbar","options"),KviOption_boolUseTaskBarActivityMeter);
#ifdef COMPILE_INFO_TIPS
	mergeTip(b,__tr2qs_ctx("<center>This option enables the usage of the taskbar activity meter. " \
		"Each window entry will have a small indicator of the activity that is going on in that window. " \
		"The indicator is a small square that changes colors, dark colors mean low activity, " \
		"while bright colors signal high activity. KVIrc also uses some heuristics to determine " \
		"whether the activity is somewhat \"human\" or it is generated by automated entities (such as bots " \
		"or IRC servers). \"Human\" activity causes the indicator to be shaded red while automated " \
		"activity causes the indicator to be shaded blue.</center>","options"));
#endif
	addBoolSelector(0,4,0,4,__tr2qs_ctx("Show IRC context indicator in taskbar","options"),KviOption_boolUseTaskBarIrcContextIndicator);
	addBoolSelector(0,5,0,5,__tr2qs_ctx("Enable window tooltips","options"),KviOption_boolShowTaskBarToolTips);
	addRowSpacer(0,6,0,6);
}


KviTaskBarOptionsWidget::~KviTaskBarOptionsWidget()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


KviTreeTaskBarOptionsWidget::KviTreeTaskBarOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"treetaskbar_options_widget")
{
}

KviTreeTaskBarOptionsWidget::~KviTreeTaskBarOptionsWidget()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


KviTreeTaskBarForegroundOptionsWidget::KviTreeTaskBarForegroundOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"treetaskbar_options_widget")
{
	createLayout(3,1);
	
	KviTalGroupBox *g = addGroupBox(0,0,0,0,2,Qt::Horizontal,__tr2qs_ctx("Text/Alert Colors","options"));
	
	addColorSelector(g,__tr2qs_ctx("Normal:","options"),KviOption_colorTreeTaskBarForeground);
	addColorSelector(g,__tr2qs_ctx("Selected:","options"),KviOption_colorTreeTaskBarActiveForeground);
	addColorSelector(g,__tr2qs_ctx("Alert Level 1:","options"),KviOption_colorTreeTaskBarHighlight1Foreground);
	addColorSelector(g,__tr2qs_ctx("Alert Level 2:","options"),KviOption_colorTreeTaskBarHighlight2Foreground);
	addColorSelector(g,__tr2qs_ctx("Alert Level 3:","options"),KviOption_colorTreeTaskBarHighlight3Foreground);
	addColorSelector(g,__tr2qs_ctx("Alert Level 4:","options"),KviOption_colorTreeTaskBarHighlight4Foreground);
	addColorSelector(g,__tr2qs_ctx("Alert Level 5:","options"),KviOption_colorTreeTaskBarHighlight5Foreground);

	addColorSelector(0,1,0,1,__tr2qs_ctx("Progress bar color:","options"),KviOption_colorTreeTaskBarProgress);

	addRowSpacer(0,2,0,2);
}


KviTreeTaskBarForegroundOptionsWidget::~KviTreeTaskBarForegroundOptionsWidget()
{
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


KviTreeTaskBarBackgroundOptionsWidget::KviTreeTaskBarBackgroundOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"treetaskbar_options_widget")
{
	createLayout(4,2);
	
	KviTalGroupBox * g = addGroupBox(0,0,1,0,2,Qt::Horizontal,__tr2qs_ctx("Background Colors","options"));
	addColorSelector(g,__tr2qs_ctx("Normal:","options"),KviOption_colorTreeTaskBarBackground);
	addColorSelector(g,__tr2qs_ctx("Selected:","options"),KviOption_colorTreeTaskBarActiveBackground);

	addPixmapSelector(0,1,1,1,__tr2qs_ctx("Background image:","options"),KviOption_pixmapTreeTaskBarBackground);

	addLabel(0,2,0,2,__tr2qs_ctx("Horizontal align:","options"));
	m_pHorizontalAlign=new QComboBox(this);
	addWidgetToLayout(m_pHorizontalAlign,1,2,1,2);
	
	addLabel(0,3,0,3,__tr2qs_ctx("Vertical align:","options"));
	m_pVerticalAlign=new QComboBox(this);
	addWidgetToLayout(m_pVerticalAlign,1,3,1,3);
	
	m_pHorizontalAlign->insertItem(__tr2qs_ctx("Tile","options"));
	m_pHorizontalAlign->insertItem(__tr2qs_ctx("Left","options"));
	m_pHorizontalAlign->insertItem(__tr2qs_ctx("Right","options"));
	m_pHorizontalAlign->insertItem(__tr2qs_ctx("Center","options"));
	
	m_pVerticalAlign->insertItem(__tr2qs_ctx("Tile","options"));
	m_pVerticalAlign->insertItem(__tr2qs_ctx("Top","options"));
	m_pVerticalAlign->insertItem(__tr2qs_ctx("Bottom","options"));
	m_pVerticalAlign->insertItem(__tr2qs_ctx("Center","options"));
	
	switch( KVI_OPTION_UINT(KviOption_uintTreeTaskBarPixmapAlign) & Qt::AlignHorizontal_Mask)
	{
		case Qt::AlignLeft:
			m_pHorizontalAlign->setCurrentItem(1);
			break;
		case Qt::AlignRight:
			m_pHorizontalAlign->setCurrentItem(2);
			break;
		case Qt::AlignHCenter:
			m_pHorizontalAlign->setCurrentItem(3);
			break;
		default:
			m_pHorizontalAlign->setCurrentItem(0);
	}
	
	switch( KVI_OPTION_UINT(KviOption_uintTreeTaskBarPixmapAlign) & Qt::AlignVertical_Mask)
	{
		case Qt::AlignTop:
			m_pVerticalAlign->setCurrentItem(1);
			break;
		case Qt::AlignBottom:
			m_pVerticalAlign->setCurrentItem(2);
			break;
		case Qt::AlignVCenter:
			m_pVerticalAlign->setCurrentItem(3);
			break;
		default:
			m_pVerticalAlign->setCurrentItem(0);
	}

	layout()->setRowStretch(1,1);
}


KviTreeTaskBarBackgroundOptionsWidget::~KviTreeTaskBarBackgroundOptionsWidget()
{
}

void KviTreeTaskBarBackgroundOptionsWidget::commit()
{
	KviOptionsWidget::commit();

	int iFlags=0;
	switch(m_pHorizontalAlign->currentItem())
	{
		case 1:
			iFlags|=Qt::AlignLeft;
			break;
		case 2:
			iFlags|=Qt::AlignRight;
			break;
		case 3:
			iFlags|=Qt::AlignHCenter;
			break;
	}
	switch(m_pVerticalAlign->currentItem())
	{
		case 1:
			iFlags|=Qt::AlignTop;
			break;
		case 2:
			iFlags|=Qt::AlignBottom;
			break;
		case 3:
			iFlags|=Qt::AlignVCenter;
			break;
	}
	
	KVI_OPTION_UINT(KviOption_uintTreeTaskBarPixmapAlign)=iFlags;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KviTreeTaskBarFeaturesOptionsWidget::KviTreeTaskBarFeaturesOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"treetaskbar_options_widget")
{
	createLayout(4,1);

	addBoolSelector(0,0,1,0,__tr2qs_ctx("Show header","options"),KviOption_boolShowTreeTaskbarHeader);
	
	addUIntSelector(0,1,0,1,__tr2qs_ctx("Minimum width:","options"),KviOption_uintTreeTaskBarMinimumWidth,24,1024,125);
	addUIntSelector(0,2,0,2,__tr2qs_ctx("Maximum width:","options"),KviOption_uintTreeTaskBarMaximumWidth,24,9999,125);

	addRowSpacer(0,3,0,3);
}


KviTreeTaskBarFeaturesOptionsWidget::~KviTreeTaskBarFeaturesOptionsWidget()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


KviClassicTaskBarOptionsWidget::KviClassicTaskBarOptionsWidget(QWidget * parent)
: KviOptionsWidget(parent,"classictaskbar_options_widget")
{
	createLayout(8,1);
	addFontSelector(0,0,0,0,__tr2qs_ctx("Font:","options"),KviOption_fontTaskbar);
	KviTalGroupBox *g = addGroupBox(0,1,0,1,2,Qt::Horizontal,__tr2qs_ctx("Text/Alert Colors","options"));
	addColorSelector(g,__tr2qs_ctx("Normal:","options"),KviOption_colorTaskBarNormalText);
	addColorSelector(g,__tr2qs_ctx("Minimized:","options"), KviOption_colorTaskBarMinimizedText);
	addColorSelector(g,__tr2qs_ctx("Alert Level 1:","options"),KviOption_colorTaskBarHighlight1Text);
	addColorSelector(g,__tr2qs_ctx("Alert Level 2:","options"),KviOption_colorTaskBarHighlight2Text);
	addColorSelector(g,__tr2qs_ctx("Alert Level 3:","options"),KviOption_colorTaskBarHighlight3Text);
	addColorSelector(g,__tr2qs_ctx("Alert Level 4:","options"),KviOption_colorTaskBarHighlight4Text);
	addColorSelector(g,__tr2qs_ctx("Alert Level 5:","options"),KviOption_colorTaskBarHighlight5Text);
	addColorSelector(0,2,0,2,__tr2qs_ctx("Progress bar color:","options"),KviOption_colorTaskBarProgressBar);
	addUIntSelector(0,3,0,3,__tr2qs_ctx("Minimum width of buttons:","options"),KviOption_uintTaskBarButtonMinWidth,24,9999,100);
	//addUIntSelector(0,4,0,4,__tr2qs_ctx("Maximum number of rows:","options"),KviOption_uintTaskBarMaximumRows,1,16,2);
	addBoolSelector(0,4,0,4,__tr2qs_ctx("Set maximum button width","options"),KviOption_boolClassicTaskBarSetMaximumButtonWidth);
	addUIntSelector(0,5,0,5,__tr2qs_ctx("Maximum width of buttons:","options"),KviOption_uintClassicTaskBarMaximumButtonWidth,24,9999,100);
	addBoolSelector(0,6,0,6,__tr2qs_ctx("Use flat buttons","options"),KviOption_boolUseFlatClassicTaskbarButtons);
	addRowSpacer(0,7,0,7);
}


KviClassicTaskBarOptionsWidget::~KviClassicTaskBarOptionsWidget()
{
}

#include "m_optw_taskbar.moc"