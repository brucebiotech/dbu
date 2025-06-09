/*
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _device_fz1_pins_H_
#define _device_fz1_pins_H_

#ifdef IMPLEMENT_FPDU
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

//
// SWDCLK
//
static void
fw1_swclk_tck_set (void) {
	HAL_GPIO_FW1_SWCLK_TCK_set ();
}

static void
fw1_swclk_tck_clear (void) {
	HAL_GPIO_FW1_SWCLK_TCK_clr ();
}

static void
fw1_swclk_tck_write (int level) {
	HAL_GPIO_FW1_SWCLK_TCK_write (level);
}

static int
fw1_swclk_tck_read (void) {
	return HAL_GPIO_FW1_SWCLK_TCK_read ();
}

static void
fw1_swclk_tck_in (void) {
	HAL_GPIO_FW1_SWCLK_TCK_in ();
}

static void
fw1_swclk_tck_out (void) {
	HAL_GPIO_FW1_SWCLK_TCK_out ();
}

//
// SWDIO
//
static void
fw1_swdio_write (int level) {
	HAL_GPIO_FW1_SWDIO_TMS_write (level);
}

static int
fw1_swdio_read (void) {
	return HAL_GPIO_FW1_SWDIO_TMS_read ();
}

static void
fw1_swdio_in (void) {
	HAL_GPIO_FW1_SWDIO_TMS_in ();
}

static void
fw1_swdio_out (void) {
	HAL_GPIO_FW1_SWDIO_TMS_out ();
}

static void
fw1_swdio_set (void) {
	HAL_GPIO_FW1_SWDIO_TMS_set ();
}

static void
fw1_swdio_clear (void) {
	HAL_GPIO_FW1_SWDIO_TMS_clr ();
}

//
// reset
//
static void
fw1_reset_write (int level) {
	HAL_GPIO_FW1_nRESET_write (level);
}

static void
fw1_reset_active (int level) {
	HAL_GPIO_FW1_nRESET_write_state (level);
}

static int
fw1_reset_read (void) {
	return HAL_GPIO_FW1_nRESET_read ();
}

static void
fw1_reset_in (void) {
	HAL_GPIO_FW1_nRESET_in ();
}

static void
fw1_reset_out (void) {
	HAL_GPIO_FW1_nRESET_out ();
}

static void
fw1_reset_set (void) {
	HAL_GPIO_FW1_nRESET_set ();
}

static void
fw1_reset_clear (void) {
	HAL_GPIO_FW1_nRESET_clr ();
}

#endif /* IMPLEMENT_FPDU */
#endif

