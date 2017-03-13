// Functions.h
namespace Elevator{
	class Functions{
		public:
			// Returns a + b
			static double TimeToDestiny(double origin_floor, double destiny_floor, double time_sended, double time_now);
			static double ChooseController(double est1, double est2, double of1, double of2, double ff1, double ff2, double t1, double t2, double floor, double t);
  };
}
