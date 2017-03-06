// Functions.h
namespace Elevator{
	class Functions{
		public:
			// Returns a + b
			static double TimeToDestiny(int origin_floor, int destiny_floor, double time_sended, double time_now);
			static int ChooseController(int est1, int est2, int of1, int of2, int ff1, int ff2, double t1, double t2, int floor, double t);
  };
}
