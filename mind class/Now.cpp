// the NOW
#include "now.h"

// start
void JB_Now::start()
{
	go = true;
	the_createive_mind.InitilzeLifeCycle();
}
//stop
void JB_Now::stop()
{
	go = false;
}
// update
void JB_Now::thought()
{
	if(go == true)
	{
		cout << "\nMind is acitive I shall Think->\n{";
		the_createive_mind.thought();
		cout << "\n}\n";

	}
}
// im alive
bool JB_Now::im_alive()
{
	return go;
}
// still the mind (for now)
void DestroyMind(JB_Now* menow)
{
	menow->stop();
}


