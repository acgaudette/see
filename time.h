#ifndef MIN_DT
#define MIN_DT 1e-4
#endif

#ifndef FIXED_DT
#define FIXED_DT (1.f / 30.f)
#endif

extern struct _time {
	struct {
		float real;
		float game;
	} el;

	struct {
		float real;
		float game;
	} dt;

	struct {
		float acc;
		float rem;
	} fixed;

	float scale; // Remember to initialize!
} _time;

static int _time_tick(float *t, float *dt)
{
	_time.el.real = *t;
	_time.dt.real = *dt;

	*dt *= _time.scale;
	if (*dt < MIN_DT) *dt = 0.f;

	_time.dt.game  = *dt;
	_time.el.game += *dt;
	*t = _time.el.game;

	_time.fixed.acc += _time.dt.game;
	return *dt > 0.f;
}

static int _time_step()
{
	if (_time.fixed.acc < FIXED_DT) {
		_time.fixed.rem = _time.fixed.acc / FIXED_DT;
		assert(is01f(_time.fixed.rem));
		return 0;
	}

	_time.fixed.acc -= FIXED_DT;
	return 1;
}