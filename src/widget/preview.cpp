#include "preview.hpp"
#include "global.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QtDebug>

namespace KomiX {

	Preview::Preview( QWidget * parent, Qt::WindowFlags f ) :
	QDialog( parent, f ),
	model_( SupportedFormatsFilter(), QDir::Files, QDir::Name, this ),
	view_( this ),
	image_( this ) {
		setModal( true );

		model_.setNameFilters( SupportedFormatsFilter() );

		view_.setModel( &model_ );
		connect( view_.selectionModel(), SIGNAL( currentChanged( const QModelIndex &, const QModelIndex & ) ), this, SLOT( viewImage_( const QModelIndex &, const QModelIndex & ) ) );

		image_.setFixedSize( 360, 360 );
		image_.setAlignment( Qt::AlignCenter );

		QDialogButtonBox * buttonBox = new QDialogButtonBox( QDialogButtonBox::Open | QDialogButtonBox::Cancel, Qt::Horizontal, this );
		connect( buttonBox, SIGNAL( rejected() ), this, SLOT( reject() ) );
		connect( buttonBox, SIGNAL( accepted() ), this, SLOT( openHelper_() ) );

		QHBoxLayout * topFrame = new QHBoxLayout;
		topFrame->addWidget( &view_ );
		topFrame->addWidget( &image_ );

		QVBoxLayout * mainFrame = new QVBoxLayout( this );
		mainFrame->addLayout( topFrame );
		mainFrame->addWidget( buttonBox );
	}

	void Preview::listDirectory( const QString & dirPath, const QString & filePath ) {
		view_.setRootIndex( model_.index( dirPath ) );
		view_.setCurrentIndex( model_.index( filePath ) );
		exec();
	}

	void Preview::openHelper_() {
		qDebug() << "Send: " << model_.filePath( view_.currentIndex() );
		emit open( model_.filePath( view_.currentIndex() ) );
		accept();
	}

	void Preview::viewImage_( const QModelIndex & current, const QModelIndex & /* previous */ ) {
		image_.setPixmap( QPixmap( model_.filePath( current ) ).scaled( image_.size(), Qt::KeepAspectRatio ) );
	}

}