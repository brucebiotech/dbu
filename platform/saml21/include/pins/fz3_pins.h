/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _device_fz3_pins_H_
#define _device_fz3_pins_H_

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

static void
fw3_swclk_tck_set (void) {
	HAL_GPIO_FW3_SWCLK_TCK_set ();
}

static void
fw3_swclk_tck_clear (void) {
	HAL_GPIO_FW3_SWCLK_TCK_clr ();
}

static void
fw3_swclk_tck_write (int state) {
	HAL_GPIO_FW3_SWCLK_TCK_write (state);
}

static int
fw3_swclk_tck_read (void) {
	return HAL_GPIO_FW3_SWCLK_TCK_read ();
}

static void
fw3_swclk_tck_in (void) {
	HAL_GPIO_FW3_SWCLK_TCK_in ();
}

static void
fw3_swclk_tck_out (void) {
	HAL_GPIO_FW3_SWCLK_TCK_out ();
}

static void
fw3_swdio_write (int state) {
	HAL_GPIO_FW3_SWDIO_TMS_write (state);
}

static int
fw3_swdio_read (void) {
	return HAL_GPIO_FW3_SWDIO_TMS_read ();
}

static void
fw3_swdio_in (void) {
	HAL_GPIO_FW3_SWDIO_TMS_in ();
}

static void
fw3_swdio_out (void) {
	HAL_GPIO_FW3_SWDIO_TMS_out ();
}

static void
fw3_swdio_set (void) {
	HAL_GPIO_FW3_SWDIO_TMS_set ();
}

static void
fw3_swdio_clear (void) {
	HAL_GPIO_FW3_SWDIO_TMS_clr ();
}

static void
fw3_reset_write (int state) {
	HAL_GPIO_FW3_nRESET_write (state);
}

static void
fw3_reset_active (int state) {
	HAL_GPIO_FW3_nRESET_write_state (state);
}

static int
fw3_reset_read (void) {
	return HAL_GPIO_FW3_nRESET_read ();
}

static void
fw3_reset_in (void) {
	HAL_GPIO_FW3_nRESET_in ();
}

static void
fw3_reset_out (void) {
	HAL_GPIO_FW3_nRESET_out ();
}

static void
fw3_reset_set (void) {
	HAL_GPIO_FW3_nRESET_set ();
}

static void
fw3_reset_clear (void) {
	HAL_GPIO_FW3_nRESET_clr ();
}


#endif /* IMPLEMENT_FPDU */
#endif

