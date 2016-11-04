#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

// Ignore Warning
#ifdef _MSC_VER
#pragma warning(disable: 4127) // disable warning 4127
#endif

#include <QtGui>

// Enable Warning
#ifdef _MSC_VER
#pragma warning(default: 4127) // disable warning 4127
#endif

#include "portaudio.h"
#include "opus.h"

#include <fstream>
#include <cstdlib>

int             main(int argc, char **argv)
{
  std::ifstream ifile("/tmp/test.txt");

  // PortAudio
  Pa_Initialize();
  
  // OPUS
  opus_encoder_destroy(nullptr);
  
  // BOOST
  boost::asio::io_service io_service;
  try {
    boost::archive::binary_iarchive iTextArchive(ifile);
  } catch (boost::archive::archive_exception) {
  }

  // QT
  QApplication app(argc, argv);
  QWidget window;
  window.resize(320, 240);
  window.show();
  window.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));
  return app.exec();
}
