;X16 Kernal data offsets / subroutine definitions, which are not present in CC65.
;Original code by SlithyMatt (taken from https://github.com/SlithyMatt/x16-hello-cc65/blob/master/asm/x16.inc)
;Modified by nb-programmer (To remove stuff already present in the cc65 include file)

.ifndef X16_INC
X16_INC  = 1

.ifndef __CX16__
__CX16__ = 1
.endif

; X16 addresses, values, and macros
; Accurate for ROM release R38

SD_DEVICE   = 8 ; also host file system on emulator if no SD image mounted
DISK_DEVICE = SD_DEVICE ; change if to be loaded off IEC device


; RAM Addresses

; Zero-Page userspace
ZP_PTR_1          = $7E   ; four pointers for temporary use only
ZP_PTR_2          = $22
ZP_PTR_3          = $24
ZP_PTR_4          = $26

; ROM Banks
KERNAL_ROM_BANK   = 0
KEYBOARD_ROM_BANK = 1
CBDOS_ROM_BANK    = 2
GEOS_ROM_BANK     = 3
BASIC_ROM_BANK    = 4
MONITOR_ROM_BANK  = 5
CHARSET_ROM_BANK  = 6

; Banked Addresses
RAM_WIN           = $A000
RAM_WIN_SIZE      = $2000
ROM_WIN           = $C000

; Kernal Subroutines
ENTROPY_GET                   := $FECF
CONSOLE_set_paging_message    := $FED5
CONSOLE_put_image             := $FED8
CONSOLE_init                  := $FEDB
CONSOLE_put_char              := $FEDE
CONSOLE_get_char              := $FEE1
MEMORY_FILL                   := $FEE4
MEMORY_COPY                   := $FEE7
MEMORY_CRC                    := $FEEA
MEMORY_DECOMPRESS             := $FEED
SPRITE_set_image              := $FEF0
SPRITE_set_position           := $FEF3
FB_init                       := $FEF6
FB_get_info                   := $FEF9
FB_set_palette                := $FEFC
FB_cursor_position            := $FEFF
FB_cursor_next_line           := $FF02
FB_get_pixel                  := $FF05
FB_get_pixels                 := $FF08
FB_set_pixel                  := $FF0B
FB_set_pixels                 := $FF0E
FB_set_8_pixels               := $FF11
FB_set_8_pixels_opaque        := $FF14
FB_fill_pixels                := $FF17
FB_filter_pixels              := $FF1A
FB_move_pixels                := $FF1D
GRAPH_init                    := $FF20
GRAPH_clear                   := $FF23
GRAPH_set_window              := $FF26
GRAPH_set_colors              := $FF29
GRAPH_draw_line               := $FF2C
GRAPH_draw_rect               := $FF2F
GRAPH_move_rect               := $FF32
GRAPH_draw_oval               := $FF35
GRAPH_draw_image              := $FF38
GRAPH_set_font                := $FF3B
GRAPH_get_char_size           := $FF3E
GRAPH_put_char                := $FF41
MONITOR                       := $FF44
ENTER_BASIC                   := $FF47
CLOSE_ALL                     := $FF4A
CLOCK_SET_DATE_TIME           := $FF4D
CLOCK_GET_DATE_TIME           := $FF50
JOYSTICK_SCAN                 := $FF53
JOYSTICK_GET                  := $FF56
SCREEN_SET_MODE               := $FF5F
SCREEN_SET_CHARSET            := $FF62
PFKEY                         := $FF65
MOUSE_CONFIG                  := $FF68
MOUSE_GET                     := $FF6B
JSRFAR                        := $FF6E
MOUSE_SCAN                    := $FF71
FETCH                         := $FF74
STASH                         := $FF77
CMPARE                        := $FF7A
PRIMM                         := $FF7D

SCINIT                        := $FF81
IOINIT                        := $FF84
RAMTAS                        := $FF87
RESTOR                        := $FF8A
LKUPLA                        := $FF8D
SETMSG                        := $FF90
SECOND                        := $FF93
TKSA                          := $FF96
MEMTOP                        := $FF99
MEMBOT                        := $FF9C
SETTMO                        := $FFA2
IECIN                         := $FFA5
IECOUT                        := $FFA8
UNTALK                        := $FFAB
UNLISTEN                      := $FFAE
LISTEN                        := $FFB1
TALK                          := $FFB4
READST                        := $FFB7
SETLFS                        := $FFBA
SETNAM                        := $FFBD
OPEN                          := $FFC0
CLOSE                         := $FFC3
CHKIN                         := $FFC6
CHKOUT                        := $FFC9
CLRCHN                        := $FFCC
CHRIN                         := $FFCF
BASIN                         := CHRIN ; alias
CHROUT                        := $FFD2
BSOUT                         := CHROUT ; alias
LOAD                          := $FFD5
SAVE                          := $FFD8
SETTIM                        := $FFDB
RDTIM                         := $FFDE
STOP                          := $FFE1
GETIN                         := $FFE4
CLALL                         := $FFE7
UDTIM                         := $FFEA
SCREEN                        := $FFED
PLOT                          := $FFF0
IOBASE                        := $FFF3

; BASIC Vectors
BASIC_PANIC       := $C000
BASIC_INIT        := $C003


; VRAM Addresses
VRAM_petscii   = $0F800
VRAM_psg       = $1F9C0
VRAM_palette   = $1FA00
VRAM_sprattr   = $1FC00


;   Macros

.macro VERA_SET_ADDR addr, stride
   .ifnblank stride
      .if stride < 0
         lda #((^addr) | $08 | ((0-stride) << 4))
      .else
         lda #((^addr) | (stride << 4))
      .endif
   .else
      lda #(^addr) | $10
   .endif

   sta VERA_addr_bank
   lda #(>addr)
   sta VERA_addr_high
   lda #(<addr)
   sta VERA_addr_low
.endmacro


.endif