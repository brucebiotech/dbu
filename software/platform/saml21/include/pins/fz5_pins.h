/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _device_fz5_pins_H_
#define _device_fz5_pins_H_

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

static void
fz5_swclk_tck_set (void) {
	HAL_GPIO_FZ5_SWCLK_TCK_set ();
}

static void
fz5_swclk_tck_clear (void) {
	HAL_GPIO_FZ5_SWCLK_TCK_clr ();
}

static void
fz5_swclk_tck_write (int state) {
	HAL_GPIO_FZ5_SWCLK_TCK_write (state);
}

static int
fz5_swclk_tck_read (void) {
	return HAL_GPIO_FZ5_SWCLK_TCK_read ();
}

static void
fz5_swclk_tck_in (void) {
	HAL_GPIO_FZ5_SWCLK_TCK_in ();
}

static void
fz5_swclk_tck_out (void) {
	HAL_GPIO_FZ5_SWCLK_TCK_out ();
}

static void
fz5_swdio_write (int state) {
	HAL_GPIO_FZ5_SWDIO_TMS_write (state);
}

static int
fz5_swdio_read (void) {
	return HAL_GPIO_FZ5_SWDIO_TMS_read ();
}

static void
fz5_swdio_in (void) {
	HAL_GPIO_FZ5_SWDIO_TMS_in ();
}

static void
fz5_swdio_out (void) {
	HAL_GPIO_FZ5_SWDIO_TMS_out ();
}

static void
fz5_swdio_set (void) {
	HAL_GPIO_FZ5_SWDIO_TMS_set ();
}

static void
fz5_swdio_clear (void) {
	HAL_GPIO_FZ5_SWDIO_TMS_clr ();
}

static void
fz5_reset_write (int state) {
	HAL_GPIO_FZ5_nRESET_write (state);
}

static void
fz5_reset_active (int state) {
	HAL_GPIO_FZ5_nRESET_write_state (state);
}

static int
fz5_reset_read (void) {
	return HAL_GPIO_FZ5_nRESET_read ();
}

static void
fz5_reset_in (void) {
	HAL_GPIO_FZ5_nRESET_in ();
}

static void
fz5_reset_out (void) {
	HAL_GPIO_FZ5_nRESET_out ();
}

static void
fz5_reset_set (void) {
	HAL_GPIO_FZ5_nRESET_set ();
}

static void
fz5_reset_clear (void) {
	HAL_GPIO_FZ5_nRESET_clr ();
}



#endif /* IMPLEMENT_FPDU */
#endif

