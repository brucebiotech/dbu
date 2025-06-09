/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _device_fz4_pins_H_
#define _device_fz4_pins_H_

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

static void
fw4_swclk_tck_set (void) {
	HAL_GPIO_FW4_SWCLK_TCK_set ();
}

static void
fw4_swclk_tck_clear (void) {
	HAL_GPIO_FW4_SWCLK_TCK_clr ();
}

static void
fw4_swclk_tck_write (int state) {
	HAL_GPIO_FW4_SWCLK_TCK_write (state);
}

static int
fw4_swclk_tck_read (void) {
	return HAL_GPIO_FW4_SWCLK_TCK_read ();
}

static void
fw4_swclk_tck_in (void) {
	HAL_GPIO_FW4_SWCLK_TCK_in ();
}

static void
fw4_swclk_tck_out (void) {
	HAL_GPIO_FW4_SWCLK_TCK_out ();
}

static void
fw4_swdio_write (int state) {
	HAL_GPIO_FW4_SWDIO_TMS_write (state);
}

static int
fw4_swdio_read (void) {
	return HAL_GPIO_FW4_SWDIO_TMS_read ();
}

static void
fw4_swdio_in (void) {
	HAL_GPIO_FW4_SWDIO_TMS_in ();
}

static void
fw4_swdio_out (void) {
	HAL_GPIO_FW4_SWDIO_TMS_out ();
}

static void
fw4_swdio_set (void) {
	HAL_GPIO_FW4_SWDIO_TMS_set ();
}

static void
fw4_swdio_clear (void) {
	HAL_GPIO_FW4_SWDIO_TMS_clr ();
}

static void
fw4_reset_write (int state) {
	HAL_GPIO_FW4_nRESET_write (state);
}

static void
fw4_reset_active (int state) {
	HAL_GPIO_FW4_nRESET_write_state (state);
}

static int
fw4_reset_read (void) {
	return HAL_GPIO_FW4_nRESET_read ();
}

static void
fw4_reset_in (void) {
	HAL_GPIO_FW4_nRESET_in ();
}

static void
fw4_reset_out (void) {
	HAL_GPIO_FW4_nRESET_out ();
}

static void
fw4_reset_set (void) {
	HAL_GPIO_FW4_nRESET_set ();
}

static void
fw4_reset_clear (void) {
	HAL_GPIO_FW4_nRESET_clr ();
}


#endif /* IMPLEMENT_FPDU */
#endif

