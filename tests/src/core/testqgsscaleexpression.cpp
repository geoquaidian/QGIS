/***************************************************************************
 testqgsscaleexpression.cpp
 --------------------------
 begin                : November 2014
 copyright            : (C) 2014 by Vincent Mora
 email                : vincent dor mora at oslandia dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QObject>

#include <qgsscaleexpression.h>

#if QT_VERSION < 0x40701
// See http://hub.qgis.org/issues/4284
Q_DECLARE_METATYPE( QVariant )
#endif

class TestQgsScaleExpression: public QObject
{
    Q_OBJECT
  private slots:

    void initTestCase() {}
    void cleanupTestCase() {}

    void parsing()
    {
      {
        QgsScaleExpression exp( "scale_linear(column, 1, 7, 2, 10)" );
        QCOMPARE( bool(exp), true );
        QCOMPARE( exp.type(), QgsScaleExpression::Linear );
        QCOMPARE( exp.baseExpression(), QString("column") );
        QCOMPARE( exp.minValue(), 1. );
        QCOMPARE( exp.maxValue(), 7. );
        QCOMPARE( exp.minSize(), 2. );
        QCOMPARE( exp.maxSize(), 10. );
      }
      {
        QgsScaleExpression exp( "scale_exp(column, 1, 7, 2, 10, 0.5)" );
        QCOMPARE( bool(exp), true );
        QCOMPARE( exp.type(), QgsScaleExpression::Area );
      }
      {
        QgsScaleExpression exp( "scale_exp(column, 1, 7, 2, 10, 0.57)" );
        QCOMPARE( bool(exp), true );
        QCOMPARE( exp.type(), QgsScaleExpression::Flannery );
      }
      {
        QgsScaleExpression exp( "scale_exp(column, 1, 7, 2, 10, 0.51)" );
        QCOMPARE( bool(exp), false );
        QCOMPARE( exp.type(), QgsScaleExpression::Unknown );
      }
      {
        QgsScaleExpression exp( "scale_exp(column, 1, 7, a, 10, 0.5)" );
        QCOMPARE( bool(exp), false );
        QCOMPARE( exp.type(), QgsScaleExpression::Unknown );
      }
        {
          QgsScaleExpression exp( "scale_exp(column, 1, 7)" );
          QCOMPARE( bool(exp), false );
          QCOMPARE( exp.type(), QgsScaleExpression::Unknown );
        }
      {
        QgsScaleExpression exp( QgsScaleExpression::Linear, "column", 1, 7, 2, 10 );
        QCOMPARE( bool(exp), true );
        QCOMPARE( exp.type(), QgsScaleExpression::Linear );
        QCOMPARE( exp.baseExpression(), QString("column") );
        QCOMPARE( exp.minValue(), 1. );
        QCOMPARE( exp.maxValue(), 7. );
        QCOMPARE( exp.minSize(), 2. );
        QCOMPARE( exp.maxSize(), 10. );
      }

    }
};

QTEST_MAIN( TestQgsScaleExpression )

#include "testqgsscaleexpression.moc"

