#include <iostream>
#include <fstream>
#include <string>
#include "board.pb.h"
using namespace std;

void fillBoard(boards::RefinedBoard *board)
{
	board->set_path_to_image("../share/img/refined");
	board->set_height(1024);
	board->set_width(234);
}

int main(int argc, char* argv[])
{
	// Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  boards::RefinedBoard board;

  {
	  // Read the existing address book.
	  fstream input(argv[1], ios::in | ios::binary);
	  if (!input) {
		  cout << argv[1] << ": File not found.  Creating a new file." << endl;
	  } else if (!board.ParseFromIstream(&input)) {
		  cerr << "Failed to parse address book." << endl;
		  return -1;
    }
  }

  // Add an address.
  fillBoard(&board);

  {
    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!board.SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;

}
