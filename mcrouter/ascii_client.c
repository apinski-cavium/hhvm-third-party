
#line 1 "mcrouter/lib/mc/ascii_client.rl"
/* -*- mode: c; -*- */
/* ascii_client.c is built from ascii_client.rl using ragel */

#include <ctype.h>

#include "mcrouter/lib/fbi/debug.h"
#include "mcrouter/lib/mc/_protocol.h"
#include "mcrouter/lib/mc/parser.h"
#include "mcrouter/lib/mc/msg.h"
#include "mcrouter/lib/mc/util.h"

// In libmc.client, only read the first N stats for simplicity of
// implementation. In the future it might make sense to allow an
// arbitrary number of stats, but for now that makes the code far
// easier
#define MAX_NUM_STATS 20

// Are we in the middle of a key being skipped?
#define skipping_key(parser) ((parser)->in_skipped_key &&       \
                              !(parser)->record_skip_key)


#line 26 "ascii_client.c"
static const char _ascii_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 81, 0, 0, 0, 0, 0
};

static const int ascii_start = 1;
static const int ascii_first_final = 741;
static const int ascii_error = 0;

static const int ascii_en_error_handling = 745;
static const int ascii_en_reply = 369;
static const int ascii_en_request = 583;
static const int ascii_en_request_reply = 1;


#line 493 "mcrouter/lib/mc/ascii_client.rl"


int get_reply_ragel_start_state() {
  return ascii_en_reply;
}

int get_request_ragel_start_state() {
  return ascii_en_request;
}

int get_request_reply_ragel_start_state() {
  return ascii_en_request_reply;
}

/** ascii reply parsing
    This is the real workhorse. It consumes buf, resuming the partial reply if
    one exists. As each reply is fully received, we call mcc_req_complete().
    If there is a parse error or remote error, we handle that as well. If
    there is a parse error or unrecoverable remote error, we call
    mcc_on_down() and the rest of the buffer is ignored.
    @return 0 on error */
int _on_ascii_rx(mc_parser_t* parser, char* buf, size_t nbuf) {
  FBI_ASSERT(parser);
  FBI_ASSERT(buf);
  dbg_fentry("parser=%p nbuf=%lu", parser, nbuf);

  int success = 0;
  bool isError = false;

  // ragel variables
  int cs = ascii_error; // current state
  char* p = buf;
  char* pe = buf + nbuf;
  char* eof = NULL;
  
#line 170 "ascii_client.c"
	{
	}

#line 528 "mcrouter/lib/mc/ascii_client.rl"

  char* ts = NULL; // token start
  size_t tlen = 0; // token length

  int nmsgs = 0;

  /* each iteration of this loop processes one msg, or in the case of value
     msgs the header of the msg, the body of the msg, or the tail of
     the msg. If we reach the end of buf before the end of a msg (whether
     in data or header/tail), we have a partial read and will resume when the
     next packet arrives. */
  while (p < pe) {
    /* sanity check: if memcached has a bug, or we somehow lost a msg, log
       the whatever's left and disconnect */
    if (parser->parser_state == parser_idle) {
      dbg_error("Unexpected msg '%s'", p);
      parser->parse_error(parser->context, parser->error);
      break;
    }

    FBI_ASSERT(parser->parser_state == parser_msg_header ||
           parser->parser_state == parser_body ||
           parser->parser_state == parser_partial);

    /* prepare to resume. If we're not in the middle of a msg, these will
       not be used */
    cs = parser->ragel_state;

    if (parser->parser_state == parser_msg_header) {
      if (parser->msg != NULL) {
        dbg_error("parser->msg already exists at start of new message. "
                  "Probable memory leak.");
      }

      // new msg
      parser->msg = mc_msg_new(0);
      if (parser->msg == NULL) {
        parser->error = parser_out_of_memory;
        parser->resid = parser->off = 0;
        parser->parse_error(parser->context, parser->error);
        success = 0;
        goto epilogue;
      }

      cs = parser->ragel_start_state;
      parser->parser_state = parser_partial;
    }
    FBI_ASSERT(parser->msg);

    dbg_low("resid=%lu msg=%p parser_state=%s cs=%d",
            pe - p, parser->msg,
            parser_state_to_string(parser->parser_state), cs);

    if (parser->parser_state == parser_body) {
      FBI_ASSERT(pe >= p);
      size_t n = MIN(parser->resid, (size_t)(pe - p));
      memcpy(&parser->msg->value.str[parser->off], p, n);
      p += n;
      parser->off += n;
      FBI_ASSERT(parser->resid >= n);
      parser->resid -= n;
      if (parser->resid == 0) {
        FBI_ASSERT(parser->off == parser->msg->value.len);
        parser->parser_state = parser_partial;
      }
    } else {
      if (parser->partial_token) {
        // we're in the middle of a token
        ts = p;
      } else {
        ts = NULL;
      }

      /* this is where ragel emits the state machine code */
      
#line 250 "ascii_client.c"
	{
	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	switch ( cs ) {
case 1:
	switch( (*p) ) {
		case 67: goto tr2;
		case 68: goto tr3;
		case 69: goto tr4;
		case 76: goto tr5;
		case 77: goto tr6;
		case 78: goto tr7;
		case 79: goto tr8;
		case 83: goto tr9;
		case 86: goto tr10;
		case 97: goto tr11;
		case 99: goto tr12;
		case 100: goto tr13;
		case 101: goto tr14;
		case 102: goto tr15;
		case 103: goto tr16;
		case 105: goto tr17;
		case 108: goto tr18;
		case 109: goto tr19;
		case 112: goto tr20;
		case 113: goto tr21;
		case 114: goto tr22;
		case 115: goto tr23;
		case 118: goto tr24;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto tr1;
case 0:
	goto _out;
case 2:
	switch( (*p) ) {
		case 10: goto tr25;
		case 13: goto tr26;
		case 32: goto tr27;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr28;
	goto tr1;
case 741:
	goto tr1;
case 3:
	if ( (*p) == 10 )
		goto tr29;
	goto tr1;
case 4:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr31;
	}
	goto tr1;
case 5:
	if ( (*p) == 76 )
		goto tr32;
	goto tr1;
case 6:
	if ( (*p) == 73 )
		goto tr33;
	goto tr1;
case 7:
	if ( (*p) == 69 )
		goto tr34;
	goto tr1;
case 8:
	if ( (*p) == 78 )
		goto tr35;
	goto tr1;
case 9:
	if ( (*p) == 84 )
		goto tr36;
	goto tr1;
case 10:
	if ( (*p) == 95 )
		goto tr37;
	goto tr1;
case 11:
	if ( (*p) == 69 )
		goto tr38;
	goto tr1;
case 12:
	if ( (*p) == 82 )
		goto tr39;
	goto tr1;
case 13:
	if ( (*p) == 82 )
		goto tr40;
	goto tr1;
case 14:
	if ( (*p) == 79 )
		goto tr41;
	goto tr1;
case 15:
	if ( (*p) == 82 )
		goto tr42;
	goto tr1;
case 16:
	switch( (*p) ) {
		case 13: goto tr44;
		case 32: goto tr45;
	}
	goto tr43;
case 17:
	if ( (*p) == 13 )
		goto tr47;
	goto tr46;
case 18:
	switch( (*p) ) {
		case 10: goto tr48;
		case 13: goto tr47;
	}
	goto tr46;
case 742:
	if ( (*p) == 13 )
		goto tr47;
	goto tr46;
case 19:
	if ( (*p) == 13 )
		goto tr44;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr49;
	goto tr43;
case 20:
	switch( (*p) ) {
		case 13: goto tr47;
		case 32: goto tr50;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr51;
	goto tr46;
case 21:
	switch( (*p) ) {
		case 13: goto tr44;
		case 32: goto tr52;
	}
	goto tr43;
case 22:
	if ( (*p) == 13 )
		goto tr44;
	goto tr43;
case 23:
	if ( (*p) == 69 )
		goto tr53;
	goto tr1;
case 24:
	if ( (*p) == 76 )
		goto tr54;
	goto tr1;
case 25:
	if ( (*p) == 69 )
		goto tr55;
	goto tr1;
case 26:
	if ( (*p) == 84 )
		goto tr56;
	goto tr1;
case 27:
	if ( (*p) == 69 )
		goto tr57;
	goto tr1;
case 28:
	if ( (*p) == 68 )
		goto tr58;
	goto tr1;
case 743:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
	}
	goto tr1;
case 29:
	switch( (*p) ) {
		case 78: goto tr59;
		case 82: goto tr60;
		case 88: goto tr61;
	}
	goto tr1;
case 30:
	if ( (*p) == 68 )
		goto tr62;
	goto tr1;
case 31:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
	}
	goto tr1;
case 32:
	if ( (*p) == 82 )
		goto tr63;
	goto tr1;
case 33:
	if ( (*p) == 79 )
		goto tr64;
	goto tr1;
case 34:
	if ( (*p) == 82 )
		goto tr65;
	goto tr1;
case 35:
	if ( (*p) == 73 )
		goto tr66;
	goto tr1;
case 36:
	if ( (*p) == 83 )
		goto tr67;
	goto tr1;
case 37:
	if ( (*p) == 84 )
		goto tr68;
	goto tr1;
case 38:
	if ( (*p) == 83 )
		goto tr69;
	goto tr1;
case 39:
	if ( (*p) == 86 )
		goto tr70;
	goto tr1;
case 40:
	if ( (*p) == 65 )
		goto tr71;
	goto tr1;
case 41:
	if ( (*p) == 76 )
		goto tr72;
	goto tr1;
case 42:
	if ( (*p) == 85 )
		goto tr73;
	goto tr1;
case 43:
	if ( (*p) == 69 )
		goto tr74;
	goto tr1;
case 44:
	if ( (*p) == 32 )
		goto tr75;
	goto tr1;
case 45:
	switch( (*p) ) {
		case 32: goto tr75;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr76;
case 46:
	switch( (*p) ) {
		case 32: goto tr77;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr78;
case 47:
	switch( (*p) ) {
		case 32: goto tr79;
		case 45: goto tr80;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr81;
	goto tr1;
case 48:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr82;
	goto tr1;
case 49:
	if ( (*p) == 32 )
		goto tr83;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr82;
	goto tr1;
case 50:
	if ( (*p) == 32 )
		goto tr84;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr85;
	goto tr1;
case 51:
	if ( (*p) == 32 )
		goto tr86;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr87;
	goto tr1;
case 52:
	if ( (*p) == 32 )
		goto tr88;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr89;
	goto tr1;
case 53:
	switch( (*p) ) {
		case 10: goto tr90;
		case 13: goto tr91;
		case 32: goto tr92;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr93;
	goto tr1;
case 54:
	switch( (*p) ) {
		case 10: goto tr94;
		case 13: goto tr95;
	}
	goto tr1;
case 55:
	if ( (*p) == 69 )
		goto tr96;
	goto tr1;
case 56:
	if ( (*p) == 78 )
		goto tr59;
	goto tr1;
case 57:
	if ( (*p) == 10 )
		goto tr94;
	goto tr1;
case 58:
	if ( (*p) == 10 )
		goto tr97;
	goto tr1;
case 59:
	if ( (*p) == 32 )
		goto tr98;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr99;
	goto tr1;
case 60:
	switch( (*p) ) {
		case 10: goto tr100;
		case 13: goto tr101;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr102;
	goto tr1;
case 61:
	if ( (*p) == 69 )
		goto tr103;
	goto tr1;
case 62:
	if ( (*p) == 84 )
		goto tr104;
	goto tr1;
case 63:
	if ( (*p) == 65 )
		goto tr105;
	goto tr1;
case 64:
	if ( (*p) == 32 )
		goto tr106;
	goto tr1;
case 65:
	switch( (*p) ) {
		case 32: goto tr107;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr108;
case 66:
	switch( (*p) ) {
		case 32: goto tr109;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr110;
case 67:
	switch( (*p) ) {
		case 32: goto tr111;
		case 97: goto tr112;
	}
	goto tr1;
case 68:
	if ( (*p) == 103 )
		goto tr113;
	goto tr1;
case 69:
	if ( (*p) == 101 )
		goto tr114;
	goto tr1;
case 70:
	if ( (*p) == 58 )
		goto tr115;
	goto tr1;
case 71:
	switch( (*p) ) {
		case 32: goto tr115;
		case 117: goto tr117;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr116;
	goto tr1;
case 72:
	if ( (*p) == 59 )
		goto tr119;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr118;
	goto tr1;
case 73:
	switch( (*p) ) {
		case 32: goto tr120;
		case 101: goto tr121;
	}
	goto tr1;
case 74:
	if ( (*p) == 120 )
		goto tr122;
	goto tr1;
case 75:
	if ( (*p) == 112 )
		goto tr123;
	goto tr1;
case 76:
	if ( (*p) == 116 )
		goto tr124;
	goto tr1;
case 77:
	if ( (*p) == 105 )
		goto tr125;
	goto tr1;
case 78:
	if ( (*p) == 109 )
		goto tr126;
	goto tr1;
case 79:
	if ( (*p) == 101 )
		goto tr127;
	goto tr1;
case 80:
	if ( (*p) == 58 )
		goto tr128;
	goto tr1;
case 81:
	if ( (*p) == 32 )
		goto tr128;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr129;
	goto tr1;
case 82:
	if ( (*p) == 59 )
		goto tr131;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr130;
	goto tr1;
case 83:
	switch( (*p) ) {
		case 32: goto tr132;
		case 102: goto tr133;
	}
	goto tr1;
case 84:
	if ( (*p) == 114 )
		goto tr134;
	goto tr1;
case 85:
	if ( (*p) == 111 )
		goto tr135;
	goto tr1;
case 86:
	if ( (*p) == 109 )
		goto tr136;
	goto tr1;
case 87:
	if ( (*p) == 58 )
		goto tr137;
	goto tr1;
case 88:
	switch( (*p) ) {
		case 32: goto tr137;
		case 58: goto tr139;
		case 117: goto tr140;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr138;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr139;
	} else
		goto tr139;
	goto tr1;
case 89:
	switch( (*p) ) {
		case 46: goto tr141;
		case 58: goto tr143;
		case 59: goto tr144;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr142;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr143;
	} else
		goto tr143;
	goto tr1;
case 90:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr145;
	goto tr1;
case 91:
	if ( (*p) == 46 )
		goto tr146;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr147;
	goto tr1;
case 92:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr148;
	goto tr1;
case 93:
	if ( (*p) == 46 )
		goto tr149;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr150;
	goto tr1;
case 94:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr151;
	goto tr1;
case 95:
	if ( (*p) == 59 )
		goto tr144;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr152;
	goto tr1;
case 96:
	if ( (*p) == 59 )
		goto tr144;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr153;
	goto tr1;
case 97:
	if ( (*p) == 59 )
		goto tr144;
	goto tr1;
case 98:
	switch( (*p) ) {
		case 32: goto tr154;
		case 105: goto tr155;
	}
	goto tr1;
case 99:
	if ( (*p) == 115 )
		goto tr156;
	goto tr1;
case 100:
	if ( (*p) == 95 )
		goto tr157;
	goto tr1;
case 101:
	if ( (*p) == 116 )
		goto tr158;
	goto tr1;
case 102:
	if ( (*p) == 114 )
		goto tr159;
	goto tr1;
case 103:
	if ( (*p) == 97 )
		goto tr160;
	goto tr1;
case 104:
	if ( (*p) == 110 )
		goto tr161;
	goto tr1;
case 105:
	if ( (*p) == 115 )
		goto tr162;
	goto tr1;
case 106:
	if ( (*p) == 105 )
		goto tr163;
	goto tr1;
case 107:
	if ( (*p) == 101 )
		goto tr164;
	goto tr1;
case 108:
	if ( (*p) == 110 )
		goto tr165;
	goto tr1;
case 109:
	if ( (*p) == 116 )
		goto tr166;
	goto tr1;
case 110:
	if ( (*p) == 58 )
		goto tr167;
	goto tr1;
case 111:
	if ( (*p) == 32 )
		goto tr167;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr168;
	goto tr1;
case 112:
	switch( (*p) ) {
		case 10: goto tr169;
		case 13: goto tr170;
		case 32: goto tr171;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr172;
	goto tr1;
case 113:
	if ( (*p) == 10 )
		goto tr173;
	goto tr1;
case 114:
	switch( (*p) ) {
		case 10: goto tr173;
		case 13: goto tr174;
		case 32: goto tr175;
	}
	goto tr1;
case 115:
	if ( (*p) == 46 )
		goto tr149;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr176;
	goto tr1;
case 116:
	if ( (*p) == 46 )
		goto tr149;
	goto tr1;
case 117:
	if ( (*p) == 46 )
		goto tr146;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr177;
	goto tr1;
case 118:
	if ( (*p) == 46 )
		goto tr146;
	goto tr1;
case 119:
	switch( (*p) ) {
		case 58: goto tr143;
		case 59: goto tr144;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr142;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr143;
	} else
		goto tr143;
	goto tr1;
case 120:
	if ( (*p) == 110 )
		goto tr178;
	goto tr1;
case 121:
	if ( (*p) == 107 )
		goto tr179;
	goto tr1;
case 122:
	if ( (*p) == 110 )
		goto tr180;
	goto tr1;
case 123:
	if ( (*p) == 111 )
		goto tr181;
	goto tr1;
case 124:
	if ( (*p) == 119 )
		goto tr182;
	goto tr1;
case 125:
	if ( (*p) == 110 )
		goto tr183;
	goto tr1;
case 126:
	if ( (*p) == 59 )
		goto tr154;
	goto tr1;
case 127:
	if ( (*p) == 110 )
		goto tr184;
	goto tr1;
case 128:
	if ( (*p) == 107 )
		goto tr185;
	goto tr1;
case 129:
	if ( (*p) == 110 )
		goto tr186;
	goto tr1;
case 130:
	if ( (*p) == 111 )
		goto tr187;
	goto tr1;
case 131:
	if ( (*p) == 119 )
		goto tr188;
	goto tr1;
case 132:
	if ( (*p) == 110 )
		goto tr189;
	goto tr1;
case 133:
	if ( (*p) == 59 )
		goto tr190;
	goto tr1;
case 134:
	if ( (*p) == 79 )
		goto tr191;
	goto tr1;
case 135:
	if ( (*p) == 84 )
		goto tr192;
	goto tr1;
case 136:
	if ( (*p) == 95 )
		goto tr193;
	goto tr1;
case 137:
	switch( (*p) ) {
		case 70: goto tr194;
		case 83: goto tr195;
	}
	goto tr1;
case 138:
	if ( (*p) == 79 )
		goto tr196;
	goto tr1;
case 139:
	if ( (*p) == 85 )
		goto tr197;
	goto tr1;
case 140:
	if ( (*p) == 78 )
		goto tr198;
	goto tr1;
case 141:
	if ( (*p) == 68 )
		goto tr199;
	goto tr1;
case 142:
	if ( (*p) == 84 )
		goto tr200;
	goto tr1;
case 143:
	if ( (*p) == 79 )
		goto tr201;
	goto tr1;
case 144:
	if ( (*p) == 82 )
		goto tr202;
	goto tr1;
case 145:
	if ( (*p) == 69 )
		goto tr203;
	goto tr1;
case 146:
	if ( (*p) == 68 )
		goto tr204;
	goto tr1;
case 147:
	if ( (*p) == 75 )
		goto tr205;
	goto tr1;
case 148:
	switch( (*p) ) {
		case 69: goto tr206;
		case 84: goto tr207;
	}
	goto tr1;
case 149:
	if ( (*p) == 82 )
		goto tr208;
	goto tr1;
case 150:
	if ( (*p) == 86 )
		goto tr209;
	goto tr1;
case 151:
	if ( (*p) == 69 )
		goto tr210;
	goto tr1;
case 152:
	if ( (*p) == 82 )
		goto tr211;
	goto tr1;
case 153:
	if ( (*p) == 95 )
		goto tr212;
	goto tr1;
case 154:
	if ( (*p) == 69 )
		goto tr213;
	goto tr1;
case 155:
	if ( (*p) == 82 )
		goto tr214;
	goto tr1;
case 156:
	if ( (*p) == 82 )
		goto tr215;
	goto tr1;
case 157:
	if ( (*p) == 79 )
		goto tr216;
	goto tr1;
case 158:
	if ( (*p) == 82 )
		goto tr217;
	goto tr1;
case 159:
	switch( (*p) ) {
		case 13: goto tr219;
		case 32: goto tr220;
	}
	goto tr218;
case 160:
	if ( (*p) == 13 )
		goto tr222;
	goto tr221;
case 161:
	switch( (*p) ) {
		case 10: goto tr223;
		case 13: goto tr222;
	}
	goto tr221;
case 744:
	if ( (*p) == 13 )
		goto tr222;
	goto tr221;
case 162:
	if ( (*p) == 13 )
		goto tr219;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr224;
	goto tr218;
case 163:
	switch( (*p) ) {
		case 13: goto tr222;
		case 32: goto tr225;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr226;
	goto tr221;
case 164:
	switch( (*p) ) {
		case 13: goto tr219;
		case 32: goto tr227;
	}
	goto tr218;
case 165:
	if ( (*p) == 13 )
		goto tr219;
	goto tr218;
case 166:
	switch( (*p) ) {
		case 65: goto tr228;
		case 79: goto tr229;
	}
	goto tr1;
case 167:
	switch( (*p) ) {
		case 76: goto tr230;
		case 84: goto tr231;
	}
	goto tr1;
case 168:
	if ( (*p) == 69 )
		goto tr232;
	goto tr1;
case 169:
	if ( (*p) == 95 )
		goto tr233;
	goto tr1;
case 170:
	if ( (*p) == 83 )
		goto tr234;
	goto tr1;
case 171:
	if ( (*p) == 84 )
		goto tr235;
	goto tr1;
case 172:
	if ( (*p) == 79 )
		goto tr236;
	goto tr1;
case 173:
	if ( (*p) == 82 )
		goto tr237;
	goto tr1;
case 174:
	if ( (*p) == 69 )
		goto tr238;
	goto tr1;
case 175:
	if ( (*p) == 68 )
		goto tr239;
	goto tr1;
case 176:
	switch( (*p) ) {
		case 10: goto tr240;
		case 13: goto tr241;
	}
	goto tr1;
case 177:
	if ( (*p) == 10 )
		goto tr240;
	goto tr1;
case 178:
	if ( (*p) == 32 )
		goto tr242;
	goto tr1;
case 179:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) <= 32 )
		goto tr1;
	goto tr243;
case 180:
	switch( (*p) ) {
		case 32: goto tr244;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr245;
case 181:
	switch( (*p) ) {
		case 32: goto tr246;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr247;
case 182:
	switch( (*p) ) {
		case 10: goto tr248;
		case 13: goto tr249;
		case 32: goto tr246;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr247;
case 183:
	switch( (*p) ) {
		case 69: goto tr96;
		case 83: goto tr250;
	}
	goto tr1;
case 184:
	if ( (*p) == 84 )
		goto tr251;
	goto tr1;
case 185:
	if ( (*p) == 65 )
		goto tr252;
	goto tr1;
case 186:
	if ( (*p) == 84 )
		goto tr231;
	goto tr1;
case 187:
	if ( (*p) == 10 )
		goto tr253;
	goto tr1;
case 188:
	switch( (*p) ) {
		case 10: goto tr248;
		case 13: goto tr249;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr254;
case 189:
	if ( (*p) == 82 )
		goto tr255;
	goto tr1;
case 190:
	if ( (*p) == 69 )
		goto tr256;
	goto tr1;
case 191:
	if ( (*p) == 68 )
		goto tr257;
	goto tr1;
case 192:
	switch( (*p) ) {
		case 65: goto tr258;
		case 69: goto tr259;
	}
	goto tr1;
case 193:
	if ( (*p) == 76 )
		goto tr260;
	goto tr1;
case 194:
	if ( (*p) == 85 )
		goto tr261;
	goto tr1;
case 195:
	if ( (*p) == 69 )
		goto tr262;
	goto tr1;
case 196:
	if ( (*p) == 32 )
		goto tr263;
	goto tr1;
case 197:
	switch( (*p) ) {
		case 32: goto tr264;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr265;
case 198:
	switch( (*p) ) {
		case 32: goto tr266;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr267;
case 199:
	if ( (*p) == 32 )
		goto tr268;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr269;
	goto tr1;
case 200:
	if ( (*p) == 32 )
		goto tr270;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr271;
	goto tr1;
case 201:
	if ( (*p) == 32 )
		goto tr272;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr273;
	goto tr1;
case 202:
	switch( (*p) ) {
		case 10: goto tr274;
		case 13: goto tr275;
		case 32: goto tr276;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr277;
	goto tr1;
case 203:
	switch( (*p) ) {
		case 10: goto tr173;
		case 13: goto tr174;
	}
	goto tr1;
case 204:
	if ( (*p) == 10 )
		goto tr278;
	goto tr1;
case 205:
	if ( (*p) == 32 )
		goto tr279;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr280;
	goto tr1;
case 206:
	switch( (*p) ) {
		case 10: goto tr281;
		case 13: goto tr282;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr283;
	goto tr1;
case 207:
	if ( (*p) == 82 )
		goto tr284;
	goto tr1;
case 208:
	if ( (*p) == 83 )
		goto tr285;
	goto tr1;
case 209:
	if ( (*p) == 73 )
		goto tr286;
	goto tr1;
case 210:
	if ( (*p) == 79 )
		goto tr287;
	goto tr1;
case 211:
	if ( (*p) == 78 )
		goto tr288;
	goto tr1;
case 212:
	if ( (*p) == 32 )
		goto tr289;
	goto tr1;
case 213:
	switch( (*p) ) {
		case 10: goto tr291;
		case 13: goto tr292;
	}
	goto tr290;
case 214:
	switch( (*p) ) {
		case 10: goto tr294;
		case 13: goto tr295;
	}
	goto tr293;
case 215:
	switch( (*p) ) {
		case 100: goto tr296;
		case 112: goto tr297;
	}
	goto tr1;
case 216:
	switch( (*p) ) {
		case 100: goto tr298;
		case 109: goto tr299;
	}
	goto tr1;
case 217:
	if ( (*p) == 32 )
		goto tr300;
	goto tr1;
case 218:
	switch( (*p) ) {
		case 32: goto tr300;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr301;
case 219:
	switch( (*p) ) {
		case 32: goto tr302;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr303;
case 220:
	if ( (*p) == 32 )
		goto tr304;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr305;
	goto tr1;
case 221:
	if ( (*p) == 32 )
		goto tr306;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr307;
	goto tr1;
case 222:
	if ( (*p) == 32 )
		goto tr308;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr309;
	goto tr1;
case 223:
	if ( (*p) == 32 )
		goto tr310;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr311;
	goto tr1;
case 224:
	if ( (*p) == 32 )
		goto tr312;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr313;
	goto tr1;
case 225:
	switch( (*p) ) {
		case 10: goto tr314;
		case 13: goto tr315;
		case 32: goto tr316;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr317;
	goto tr1;
case 226:
	if ( (*p) == 10 )
		goto tr318;
	goto tr1;
case 227:
	switch( (*p) ) {
		case 10: goto tr318;
		case 13: goto tr319;
		case 32: goto tr320;
		case 110: goto tr321;
	}
	goto tr1;
case 228:
	if ( (*p) == 111 )
		goto tr322;
	goto tr1;
case 229:
	if ( (*p) == 114 )
		goto tr323;
	goto tr1;
case 230:
	if ( (*p) == 101 )
		goto tr324;
	goto tr1;
case 231:
	if ( (*p) == 112 )
		goto tr325;
	goto tr1;
case 232:
	if ( (*p) == 108 )
		goto tr326;
	goto tr1;
case 233:
	if ( (*p) == 121 )
		goto tr327;
	goto tr1;
case 234:
	switch( (*p) ) {
		case 10: goto tr328;
		case 13: goto tr329;
		case 32: goto tr330;
	}
	goto tr1;
case 235:
	switch( (*p) ) {
		case 10: goto tr318;
		case 13: goto tr319;
		case 32: goto tr331;
	}
	goto tr1;
case 236:
	if ( (*p) == 105 )
		goto tr332;
	goto tr1;
case 237:
	if ( (*p) == 110 )
		goto tr333;
	goto tr1;
case 238:
	if ( (*p) == 32 )
		goto tr334;
	goto tr1;
case 239:
	if ( (*p) == 32 )
		goto tr335;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr336;
	goto tr1;
case 240:
	switch( (*p) ) {
		case 10: goto tr337;
		case 13: goto tr338;
		case 32: goto tr335;
	}
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr336;
	goto tr1;
case 241:
	switch( (*p) ) {
		case 10: goto tr337;
		case 13: goto tr338;
	}
	if ( 32 <= (*p) && (*p) <= 126 )
		goto tr339;
	goto tr1;
case 242:
	if ( (*p) == 112 )
		goto tr340;
	goto tr1;
case 243:
	if ( (*p) == 101 )
		goto tr341;
	goto tr1;
case 244:
	if ( (*p) == 110 )
		goto tr342;
	goto tr1;
case 245:
	if ( (*p) == 100 )
		goto tr343;
	goto tr1;
case 246:
	if ( (*p) == 97 )
		goto tr344;
	goto tr1;
case 247:
	if ( (*p) == 115 )
		goto tr345;
	goto tr1;
case 248:
	if ( (*p) == 32 )
		goto tr346;
	goto tr1;
case 249:
	switch( (*p) ) {
		case 32: goto tr347;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr348;
case 250:
	switch( (*p) ) {
		case 32: goto tr349;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr350;
case 251:
	if ( (*p) == 32 )
		goto tr351;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr352;
	goto tr1;
case 252:
	if ( (*p) == 32 )
		goto tr353;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr354;
	goto tr1;
case 253:
	if ( (*p) == 32 )
		goto tr355;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr356;
	goto tr1;
case 254:
	if ( (*p) == 32 )
		goto tr357;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr358;
	goto tr1;
case 255:
	if ( (*p) == 32 )
		goto tr359;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr360;
	goto tr1;
case 256:
	if ( (*p) == 32 )
		goto tr361;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr362;
	goto tr1;
case 257:
	if ( (*p) == 32 )
		goto tr363;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr364;
	goto tr1;
case 258:
	switch( (*p) ) {
		case 10: goto tr365;
		case 13: goto tr366;
		case 32: goto tr367;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr368;
	goto tr1;
case 259:
	if ( (*p) == 101 )
		goto tr369;
	goto tr1;
case 260:
	switch( (*p) ) {
		case 99: goto tr370;
		case 108: goto tr371;
	}
	goto tr1;
case 261:
	if ( (*p) == 114 )
		goto tr372;
	goto tr1;
case 262:
	if ( (*p) == 32 )
		goto tr373;
	goto tr1;
case 263:
	switch( (*p) ) {
		case 32: goto tr373;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr374;
case 264:
	switch( (*p) ) {
		case 32: goto tr375;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr376;
case 265:
	if ( (*p) == 32 )
		goto tr377;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr378;
	goto tr1;
case 266:
	switch( (*p) ) {
		case 10: goto tr379;
		case 13: goto tr380;
		case 32: goto tr381;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr382;
	goto tr1;
case 267:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr383;
		case 110: goto tr384;
	}
	goto tr1;
case 268:
	if ( (*p) == 111 )
		goto tr385;
	goto tr1;
case 269:
	if ( (*p) == 114 )
		goto tr386;
	goto tr1;
case 270:
	if ( (*p) == 101 )
		goto tr387;
	goto tr1;
case 271:
	if ( (*p) == 112 )
		goto tr388;
	goto tr1;
case 272:
	if ( (*p) == 108 )
		goto tr389;
	goto tr1;
case 273:
	if ( (*p) == 121 )
		goto tr390;
	goto tr1;
case 274:
	switch( (*p) ) {
		case 10: goto tr391;
		case 13: goto tr392;
		case 32: goto tr393;
	}
	goto tr1;
case 275:
	if ( (*p) == 101 )
		goto tr394;
	goto tr1;
case 276:
	if ( (*p) == 116 )
		goto tr395;
	goto tr1;
case 277:
	if ( (*p) == 101 )
		goto tr396;
	goto tr1;
case 278:
	if ( (*p) == 32 )
		goto tr397;
	goto tr1;
case 279:
	switch( (*p) ) {
		case 32: goto tr397;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr398;
case 280:
	switch( (*p) ) {
		case 10: goto tr399;
		case 13: goto tr400;
		case 32: goto tr401;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr402;
case 281:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr403;
		case 110: goto tr384;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr404;
	goto tr1;
case 282:
	switch( (*p) ) {
		case 10: goto tr405;
		case 13: goto tr406;
		case 32: goto tr407;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr408;
	goto tr1;
case 283:
	if ( (*p) == 120 )
		goto tr409;
	goto tr1;
case 284:
	if ( (*p) == 101 )
		goto tr410;
	goto tr1;
case 285:
	if ( (*p) == 99 )
		goto tr333;
	goto tr1;
case 286:
	if ( (*p) == 108 )
		goto tr411;
	goto tr1;
case 287:
	if ( (*p) == 117 )
		goto tr412;
	goto tr1;
case 288:
	if ( (*p) == 115 )
		goto tr413;
	goto tr1;
case 289:
	if ( (*p) == 104 )
		goto tr414;
	goto tr1;
case 290:
	if ( (*p) == 95 )
		goto tr415;
	goto tr1;
case 291:
	switch( (*p) ) {
		case 97: goto tr416;
		case 114: goto tr417;
	}
	goto tr1;
case 292:
	if ( (*p) == 108 )
		goto tr418;
	goto tr1;
case 293:
	if ( (*p) == 108 )
		goto tr419;
	goto tr1;
case 294:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr420;
	}
	goto tr1;
case 295:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr420;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr421;
	goto tr1;
case 296:
	switch( (*p) ) {
		case 10: goto tr422;
		case 13: goto tr423;
		case 32: goto tr424;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr425;
	goto tr1;
case 297:
	if ( (*p) == 101 )
		goto tr426;
	goto tr1;
case 298:
	if ( (*p) == 103 )
		goto tr427;
	goto tr1;
case 299:
	if ( (*p) == 101 )
		goto tr428;
	goto tr1;
case 300:
	if ( (*p) == 120 )
		goto tr429;
	goto tr1;
case 301:
	if ( (*p) == 32 )
		goto tr430;
	goto tr1;
case 302:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) <= 32 )
		goto tr1;
	goto tr431;
case 303:
	switch( (*p) ) {
		case 10: goto tr399;
		case 13: goto tr400;
		case 32: goto tr432;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr433;
case 304:
	if ( (*p) == 101 )
		goto tr434;
	goto tr1;
case 305:
	if ( (*p) == 116 )
		goto tr435;
	goto tr1;
case 306:
	switch( (*p) ) {
		case 32: goto tr436;
		case 115: goto tr437;
	}
	goto tr1;
case 307:
	switch( (*p) ) {
		case 32: goto tr436;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr438;
case 308:
	switch( (*p) ) {
		case 10: goto tr439;
		case 13: goto tr440;
		case 32: goto tr441;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr442;
case 309:
	switch( (*p) ) {
		case 10: goto tr443;
		case 13: goto tr444;
		case 32: goto tr445;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr438;
case 310:
	if ( (*p) == 32 )
		goto tr436;
	goto tr1;
case 311:
	if ( (*p) == 110 )
		goto tr446;
	goto tr1;
case 312:
	if ( (*p) == 99 )
		goto tr447;
	goto tr1;
case 313:
	if ( (*p) == 114 )
		goto tr448;
	goto tr1;
case 314:
	if ( (*p) == 101 )
		goto tr449;
	goto tr1;
case 315:
	if ( (*p) == 97 )
		goto tr450;
	goto tr1;
case 316:
	if ( (*p) == 115 )
		goto tr451;
	goto tr1;
case 317:
	if ( (*p) == 101 )
		goto tr452;
	goto tr1;
case 318:
	if ( (*p) == 45 )
		goto tr453;
	goto tr1;
case 319:
	switch( (*p) ) {
		case 103: goto tr454;
		case 115: goto tr455;
	}
	goto tr1;
case 320:
	if ( (*p) == 101 )
		goto tr456;
	goto tr1;
case 321:
	if ( (*p) == 116 )
		goto tr457;
	goto tr1;
case 322:
	if ( (*p) == 101 )
		goto tr458;
	goto tr1;
case 323:
	if ( (*p) == 116 )
		goto tr459;
	goto tr1;
case 324:
	if ( (*p) == 32 )
		goto tr460;
	goto tr1;
case 325:
	switch( (*p) ) {
		case 32: goto tr460;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr461;
case 326:
	switch( (*p) ) {
		case 32: goto tr462;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr463;
case 327:
	switch( (*p) ) {
		case 32: goto tr464;
		case 45: goto tr465;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr466;
	goto tr1;
case 328:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr467;
	goto tr1;
case 329:
	if ( (*p) == 32 )
		goto tr468;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr467;
	goto tr1;
case 330:
	if ( (*p) == 101 )
		goto tr469;
	goto tr1;
case 331:
	if ( (*p) == 116 )
		goto tr470;
	goto tr1;
case 332:
	if ( (*p) == 97 )
		goto tr471;
	goto tr1;
case 333:
	if ( (*p) == 103 )
		goto tr472;
	goto tr1;
case 334:
	if ( (*p) == 101 )
		goto tr473;
	goto tr1;
case 335:
	if ( (*p) == 116 )
		goto tr474;
	goto tr1;
case 336:
	if ( (*p) == 114 )
		goto tr475;
	goto tr1;
case 337:
	if ( (*p) == 101 )
		goto tr476;
	goto tr1;
case 338:
	if ( (*p) == 112 )
		goto tr477;
	goto tr1;
case 339:
	if ( (*p) == 101 )
		goto tr478;
	goto tr1;
case 340:
	if ( (*p) == 110 )
		goto tr479;
	goto tr1;
case 341:
	if ( (*p) == 100 )
		goto tr480;
	goto tr1;
case 342:
	if ( (*p) == 117 )
		goto tr481;
	goto tr1;
case 343:
	if ( (*p) == 105 )
		goto tr482;
	goto tr1;
case 344:
	if ( (*p) == 116 )
		goto tr483;
	goto tr1;
case 345:
	if ( (*p) == 101 )
		goto tr484;
	goto tr1;
case 346:
	if ( (*p) == 112 )
		goto tr485;
	goto tr1;
case 347:
	if ( (*p) == 108 )
		goto tr486;
	goto tr1;
case 348:
	if ( (*p) == 97 )
		goto tr487;
	goto tr1;
case 349:
	if ( (*p) == 99 )
		goto tr488;
	goto tr1;
case 350:
	if ( (*p) == 101 )
		goto tr489;
	goto tr1;
case 351:
	switch( (*p) ) {
		case 101: goto tr490;
		case 104: goto tr491;
		case 116: goto tr492;
	}
	goto tr1;
case 352:
	if ( (*p) == 116 )
		goto tr493;
	goto tr1;
case 353:
	if ( (*p) == 117 )
		goto tr494;
	goto tr1;
case 354:
	if ( (*p) == 116 )
		goto tr495;
	goto tr1;
case 355:
	if ( (*p) == 100 )
		goto tr496;
	goto tr1;
case 356:
	if ( (*p) == 111 )
		goto tr497;
	goto tr1;
case 357:
	if ( (*p) == 119 )
		goto tr498;
	goto tr1;
case 358:
	if ( (*p) == 110 )
		goto tr499;
	goto tr1;
case 359:
	if ( (*p) == 97 )
		goto tr500;
	goto tr1;
case 360:
	if ( (*p) == 116 )
		goto tr501;
	goto tr1;
case 361:
	if ( (*p) == 115 )
		goto tr502;
	goto tr1;
case 362:
	switch( (*p) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr334;
	}
	goto tr1;
case 363:
	if ( (*p) == 101 )
		goto tr503;
	goto tr1;
case 364:
	if ( (*p) == 114 )
		goto tr504;
	goto tr1;
case 365:
	if ( (*p) == 115 )
		goto tr505;
	goto tr1;
case 366:
	if ( (*p) == 105 )
		goto tr506;
	goto tr1;
case 367:
	if ( (*p) == 111 )
		goto tr507;
	goto tr1;
case 368:
	if ( (*p) == 110 )
		goto tr508;
	goto tr1;
case 369:
	switch( (*p) ) {
		case 67: goto tr510;
		case 68: goto tr511;
		case 69: goto tr512;
		case 76: goto tr513;
		case 77: goto tr514;
		case 78: goto tr515;
		case 79: goto tr516;
		case 83: goto tr517;
		case 86: goto tr518;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr509;
	goto tr1;
case 370:
	switch( (*p) ) {
		case 10: goto tr519;
		case 13: goto tr520;
		case 32: goto tr521;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr522;
	goto tr1;
case 746:
	goto tr1;
case 371:
	if ( (*p) == 10 )
		goto tr523;
	goto tr1;
case 372:
	switch( (*p) ) {
		case 10: goto tr523;
		case 13: goto tr524;
		case 32: goto tr525;
	}
	goto tr1;
case 373:
	if ( (*p) == 76 )
		goto tr526;
	goto tr1;
case 374:
	if ( (*p) == 73 )
		goto tr527;
	goto tr1;
case 375:
	if ( (*p) == 69 )
		goto tr528;
	goto tr1;
case 376:
	if ( (*p) == 78 )
		goto tr529;
	goto tr1;
case 377:
	if ( (*p) == 84 )
		goto tr530;
	goto tr1;
case 378:
	if ( (*p) == 95 )
		goto tr531;
	goto tr1;
case 379:
	if ( (*p) == 69 )
		goto tr532;
	goto tr1;
case 380:
	if ( (*p) == 82 )
		goto tr533;
	goto tr1;
case 381:
	if ( (*p) == 82 )
		goto tr534;
	goto tr1;
case 382:
	if ( (*p) == 79 )
		goto tr535;
	goto tr1;
case 383:
	if ( (*p) == 82 )
		goto tr536;
	goto tr1;
case 384:
	switch( (*p) ) {
		case 13: goto tr538;
		case 32: goto tr539;
	}
	goto tr537;
case 385:
	if ( (*p) == 13 )
		goto tr541;
	goto tr540;
case 386:
	switch( (*p) ) {
		case 10: goto tr542;
		case 13: goto tr541;
	}
	goto tr540;
case 747:
	if ( (*p) == 13 )
		goto tr541;
	goto tr540;
case 387:
	if ( (*p) == 13 )
		goto tr538;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr543;
	goto tr537;
case 388:
	switch( (*p) ) {
		case 13: goto tr541;
		case 32: goto tr544;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr545;
	goto tr540;
case 389:
	switch( (*p) ) {
		case 13: goto tr538;
		case 32: goto tr546;
	}
	goto tr537;
case 390:
	if ( (*p) == 13 )
		goto tr538;
	goto tr537;
case 391:
	if ( (*p) == 69 )
		goto tr547;
	goto tr1;
case 392:
	if ( (*p) == 76 )
		goto tr548;
	goto tr1;
case 393:
	if ( (*p) == 69 )
		goto tr549;
	goto tr1;
case 394:
	if ( (*p) == 84 )
		goto tr550;
	goto tr1;
case 395:
	if ( (*p) == 69 )
		goto tr551;
	goto tr1;
case 396:
	if ( (*p) == 68 )
		goto tr552;
	goto tr1;
case 748:
	switch( (*p) ) {
		case 10: goto tr523;
		case 13: goto tr524;
	}
	goto tr1;
case 397:
	switch( (*p) ) {
		case 78: goto tr553;
		case 82: goto tr554;
		case 88: goto tr555;
	}
	goto tr1;
case 398:
	if ( (*p) == 68 )
		goto tr556;
	goto tr1;
case 399:
	switch( (*p) ) {
		case 10: goto tr523;
		case 13: goto tr524;
	}
	goto tr1;
case 400:
	if ( (*p) == 82 )
		goto tr557;
	goto tr1;
case 401:
	if ( (*p) == 79 )
		goto tr558;
	goto tr1;
case 402:
	if ( (*p) == 82 )
		goto tr559;
	goto tr1;
case 403:
	if ( (*p) == 73 )
		goto tr560;
	goto tr1;
case 404:
	if ( (*p) == 83 )
		goto tr561;
	goto tr1;
case 405:
	if ( (*p) == 84 )
		goto tr562;
	goto tr1;
case 406:
	if ( (*p) == 83 )
		goto tr563;
	goto tr1;
case 407:
	if ( (*p) == 86 )
		goto tr564;
	goto tr1;
case 408:
	if ( (*p) == 65 )
		goto tr565;
	goto tr1;
case 409:
	if ( (*p) == 76 )
		goto tr566;
	goto tr1;
case 410:
	if ( (*p) == 85 )
		goto tr567;
	goto tr1;
case 411:
	if ( (*p) == 69 )
		goto tr568;
	goto tr1;
case 412:
	if ( (*p) == 32 )
		goto tr569;
	goto tr1;
case 413:
	switch( (*p) ) {
		case 32: goto tr569;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr570;
case 414:
	switch( (*p) ) {
		case 32: goto tr571;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr572;
case 415:
	switch( (*p) ) {
		case 32: goto tr573;
		case 45: goto tr574;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr575;
	goto tr1;
case 416:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr576;
	goto tr1;
case 417:
	if ( (*p) == 32 )
		goto tr577;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr576;
	goto tr1;
case 418:
	if ( (*p) == 32 )
		goto tr578;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr579;
	goto tr1;
case 419:
	if ( (*p) == 32 )
		goto tr580;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr581;
	goto tr1;
case 420:
	if ( (*p) == 32 )
		goto tr582;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr583;
	goto tr1;
case 421:
	switch( (*p) ) {
		case 10: goto tr584;
		case 13: goto tr585;
		case 32: goto tr586;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr587;
	goto tr1;
case 422:
	switch( (*p) ) {
		case 10: goto tr588;
		case 13: goto tr589;
	}
	goto tr1;
case 423:
	if ( (*p) == 69 )
		goto tr590;
	goto tr1;
case 424:
	if ( (*p) == 78 )
		goto tr553;
	goto tr1;
case 425:
	if ( (*p) == 10 )
		goto tr588;
	goto tr1;
case 426:
	if ( (*p) == 10 )
		goto tr591;
	goto tr1;
case 427:
	if ( (*p) == 32 )
		goto tr592;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr593;
	goto tr1;
case 428:
	switch( (*p) ) {
		case 10: goto tr594;
		case 13: goto tr595;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr596;
	goto tr1;
case 429:
	if ( (*p) == 69 )
		goto tr597;
	goto tr1;
case 430:
	if ( (*p) == 84 )
		goto tr598;
	goto tr1;
case 431:
	if ( (*p) == 65 )
		goto tr599;
	goto tr1;
case 432:
	if ( (*p) == 32 )
		goto tr600;
	goto tr1;
case 433:
	switch( (*p) ) {
		case 32: goto tr601;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr602;
case 434:
	switch( (*p) ) {
		case 32: goto tr603;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr604;
case 435:
	switch( (*p) ) {
		case 32: goto tr605;
		case 97: goto tr606;
	}
	goto tr1;
case 436:
	if ( (*p) == 103 )
		goto tr607;
	goto tr1;
case 437:
	if ( (*p) == 101 )
		goto tr608;
	goto tr1;
case 438:
	if ( (*p) == 58 )
		goto tr609;
	goto tr1;
case 439:
	switch( (*p) ) {
		case 32: goto tr609;
		case 117: goto tr611;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr610;
	goto tr1;
case 440:
	if ( (*p) == 59 )
		goto tr613;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr612;
	goto tr1;
case 441:
	switch( (*p) ) {
		case 32: goto tr614;
		case 101: goto tr615;
	}
	goto tr1;
case 442:
	if ( (*p) == 120 )
		goto tr616;
	goto tr1;
case 443:
	if ( (*p) == 112 )
		goto tr617;
	goto tr1;
case 444:
	if ( (*p) == 116 )
		goto tr618;
	goto tr1;
case 445:
	if ( (*p) == 105 )
		goto tr619;
	goto tr1;
case 446:
	if ( (*p) == 109 )
		goto tr620;
	goto tr1;
case 447:
	if ( (*p) == 101 )
		goto tr621;
	goto tr1;
case 448:
	if ( (*p) == 58 )
		goto tr622;
	goto tr1;
case 449:
	if ( (*p) == 32 )
		goto tr622;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr623;
	goto tr1;
case 450:
	if ( (*p) == 59 )
		goto tr625;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr624;
	goto tr1;
case 451:
	switch( (*p) ) {
		case 32: goto tr626;
		case 102: goto tr627;
	}
	goto tr1;
case 452:
	if ( (*p) == 114 )
		goto tr628;
	goto tr1;
case 453:
	if ( (*p) == 111 )
		goto tr629;
	goto tr1;
case 454:
	if ( (*p) == 109 )
		goto tr630;
	goto tr1;
case 455:
	if ( (*p) == 58 )
		goto tr631;
	goto tr1;
case 456:
	switch( (*p) ) {
		case 32: goto tr631;
		case 58: goto tr633;
		case 117: goto tr634;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr632;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr633;
	} else
		goto tr633;
	goto tr1;
case 457:
	switch( (*p) ) {
		case 46: goto tr635;
		case 58: goto tr637;
		case 59: goto tr638;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr636;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr637;
	} else
		goto tr637;
	goto tr1;
case 458:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr639;
	goto tr1;
case 459:
	if ( (*p) == 46 )
		goto tr640;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr641;
	goto tr1;
case 460:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr642;
	goto tr1;
case 461:
	if ( (*p) == 46 )
		goto tr643;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr644;
	goto tr1;
case 462:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr645;
	goto tr1;
case 463:
	if ( (*p) == 59 )
		goto tr638;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr646;
	goto tr1;
case 464:
	if ( (*p) == 59 )
		goto tr638;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr647;
	goto tr1;
case 465:
	if ( (*p) == 59 )
		goto tr638;
	goto tr1;
case 466:
	switch( (*p) ) {
		case 32: goto tr648;
		case 105: goto tr649;
	}
	goto tr1;
case 467:
	if ( (*p) == 115 )
		goto tr650;
	goto tr1;
case 468:
	if ( (*p) == 95 )
		goto tr651;
	goto tr1;
case 469:
	if ( (*p) == 116 )
		goto tr652;
	goto tr1;
case 470:
	if ( (*p) == 114 )
		goto tr653;
	goto tr1;
case 471:
	if ( (*p) == 97 )
		goto tr654;
	goto tr1;
case 472:
	if ( (*p) == 110 )
		goto tr655;
	goto tr1;
case 473:
	if ( (*p) == 115 )
		goto tr656;
	goto tr1;
case 474:
	if ( (*p) == 105 )
		goto tr657;
	goto tr1;
case 475:
	if ( (*p) == 101 )
		goto tr658;
	goto tr1;
case 476:
	if ( (*p) == 110 )
		goto tr659;
	goto tr1;
case 477:
	if ( (*p) == 116 )
		goto tr660;
	goto tr1;
case 478:
	if ( (*p) == 58 )
		goto tr661;
	goto tr1;
case 479:
	if ( (*p) == 32 )
		goto tr661;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr662;
	goto tr1;
case 480:
	switch( (*p) ) {
		case 10: goto tr663;
		case 13: goto tr664;
		case 32: goto tr665;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr666;
	goto tr1;
case 481:
	if ( (*p) == 10 )
		goto tr667;
	goto tr1;
case 482:
	switch( (*p) ) {
		case 10: goto tr667;
		case 13: goto tr668;
		case 32: goto tr669;
	}
	goto tr1;
case 483:
	if ( (*p) == 46 )
		goto tr643;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr670;
	goto tr1;
case 484:
	if ( (*p) == 46 )
		goto tr643;
	goto tr1;
case 485:
	if ( (*p) == 46 )
		goto tr640;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr671;
	goto tr1;
case 486:
	if ( (*p) == 46 )
		goto tr640;
	goto tr1;
case 487:
	switch( (*p) ) {
		case 58: goto tr637;
		case 59: goto tr638;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr636;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr637;
	} else
		goto tr637;
	goto tr1;
case 488:
	if ( (*p) == 110 )
		goto tr672;
	goto tr1;
case 489:
	if ( (*p) == 107 )
		goto tr673;
	goto tr1;
case 490:
	if ( (*p) == 110 )
		goto tr674;
	goto tr1;
case 491:
	if ( (*p) == 111 )
		goto tr675;
	goto tr1;
case 492:
	if ( (*p) == 119 )
		goto tr676;
	goto tr1;
case 493:
	if ( (*p) == 110 )
		goto tr677;
	goto tr1;
case 494:
	if ( (*p) == 59 )
		goto tr648;
	goto tr1;
case 495:
	if ( (*p) == 110 )
		goto tr678;
	goto tr1;
case 496:
	if ( (*p) == 107 )
		goto tr679;
	goto tr1;
case 497:
	if ( (*p) == 110 )
		goto tr680;
	goto tr1;
case 498:
	if ( (*p) == 111 )
		goto tr681;
	goto tr1;
case 499:
	if ( (*p) == 119 )
		goto tr682;
	goto tr1;
case 500:
	if ( (*p) == 110 )
		goto tr683;
	goto tr1;
case 501:
	if ( (*p) == 59 )
		goto tr684;
	goto tr1;
case 502:
	if ( (*p) == 79 )
		goto tr685;
	goto tr1;
case 503:
	if ( (*p) == 84 )
		goto tr686;
	goto tr1;
case 504:
	if ( (*p) == 95 )
		goto tr687;
	goto tr1;
case 505:
	switch( (*p) ) {
		case 70: goto tr688;
		case 83: goto tr689;
	}
	goto tr1;
case 506:
	if ( (*p) == 79 )
		goto tr690;
	goto tr1;
case 507:
	if ( (*p) == 85 )
		goto tr691;
	goto tr1;
case 508:
	if ( (*p) == 78 )
		goto tr692;
	goto tr1;
case 509:
	if ( (*p) == 68 )
		goto tr693;
	goto tr1;
case 510:
	if ( (*p) == 84 )
		goto tr694;
	goto tr1;
case 511:
	if ( (*p) == 79 )
		goto tr695;
	goto tr1;
case 512:
	if ( (*p) == 82 )
		goto tr696;
	goto tr1;
case 513:
	if ( (*p) == 69 )
		goto tr697;
	goto tr1;
case 514:
	if ( (*p) == 68 )
		goto tr698;
	goto tr1;
case 515:
	if ( (*p) == 75 )
		goto tr699;
	goto tr1;
case 516:
	switch( (*p) ) {
		case 69: goto tr700;
		case 84: goto tr701;
	}
	goto tr1;
case 517:
	if ( (*p) == 82 )
		goto tr702;
	goto tr1;
case 518:
	if ( (*p) == 86 )
		goto tr703;
	goto tr1;
case 519:
	if ( (*p) == 69 )
		goto tr704;
	goto tr1;
case 520:
	if ( (*p) == 82 )
		goto tr705;
	goto tr1;
case 521:
	if ( (*p) == 95 )
		goto tr706;
	goto tr1;
case 522:
	if ( (*p) == 69 )
		goto tr707;
	goto tr1;
case 523:
	if ( (*p) == 82 )
		goto tr708;
	goto tr1;
case 524:
	if ( (*p) == 82 )
		goto tr709;
	goto tr1;
case 525:
	if ( (*p) == 79 )
		goto tr710;
	goto tr1;
case 526:
	if ( (*p) == 82 )
		goto tr711;
	goto tr1;
case 527:
	switch( (*p) ) {
		case 13: goto tr713;
		case 32: goto tr714;
	}
	goto tr712;
case 528:
	if ( (*p) == 13 )
		goto tr716;
	goto tr715;
case 529:
	switch( (*p) ) {
		case 10: goto tr717;
		case 13: goto tr716;
	}
	goto tr715;
case 749:
	if ( (*p) == 13 )
		goto tr716;
	goto tr715;
case 530:
	if ( (*p) == 13 )
		goto tr713;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr718;
	goto tr712;
case 531:
	switch( (*p) ) {
		case 13: goto tr716;
		case 32: goto tr719;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr720;
	goto tr715;
case 532:
	switch( (*p) ) {
		case 13: goto tr713;
		case 32: goto tr721;
	}
	goto tr712;
case 533:
	if ( (*p) == 13 )
		goto tr713;
	goto tr712;
case 534:
	switch( (*p) ) {
		case 65: goto tr722;
		case 79: goto tr723;
	}
	goto tr1;
case 535:
	switch( (*p) ) {
		case 76: goto tr724;
		case 84: goto tr725;
	}
	goto tr1;
case 536:
	if ( (*p) == 69 )
		goto tr726;
	goto tr1;
case 537:
	if ( (*p) == 95 )
		goto tr727;
	goto tr1;
case 538:
	if ( (*p) == 83 )
		goto tr728;
	goto tr1;
case 539:
	if ( (*p) == 84 )
		goto tr729;
	goto tr1;
case 540:
	if ( (*p) == 79 )
		goto tr730;
	goto tr1;
case 541:
	if ( (*p) == 82 )
		goto tr731;
	goto tr1;
case 542:
	if ( (*p) == 69 )
		goto tr732;
	goto tr1;
case 543:
	if ( (*p) == 68 )
		goto tr733;
	goto tr1;
case 544:
	switch( (*p) ) {
		case 10: goto tr734;
		case 13: goto tr735;
	}
	goto tr1;
case 545:
	if ( (*p) == 10 )
		goto tr734;
	goto tr1;
case 546:
	if ( (*p) == 32 )
		goto tr736;
	goto tr1;
case 547:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) <= 32 )
		goto tr1;
	goto tr737;
case 548:
	switch( (*p) ) {
		case 32: goto tr738;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr739;
case 549:
	switch( (*p) ) {
		case 32: goto tr740;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr741;
case 550:
	switch( (*p) ) {
		case 10: goto tr742;
		case 13: goto tr743;
		case 32: goto tr740;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr741;
case 551:
	switch( (*p) ) {
		case 69: goto tr590;
		case 83: goto tr744;
	}
	goto tr1;
case 552:
	if ( (*p) == 84 )
		goto tr745;
	goto tr1;
case 553:
	if ( (*p) == 65 )
		goto tr746;
	goto tr1;
case 554:
	if ( (*p) == 84 )
		goto tr725;
	goto tr1;
case 555:
	if ( (*p) == 10 )
		goto tr747;
	goto tr1;
case 556:
	switch( (*p) ) {
		case 10: goto tr742;
		case 13: goto tr743;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr748;
case 557:
	if ( (*p) == 82 )
		goto tr749;
	goto tr1;
case 558:
	if ( (*p) == 69 )
		goto tr750;
	goto tr1;
case 559:
	if ( (*p) == 68 )
		goto tr751;
	goto tr1;
case 560:
	switch( (*p) ) {
		case 65: goto tr752;
		case 69: goto tr753;
	}
	goto tr1;
case 561:
	if ( (*p) == 76 )
		goto tr754;
	goto tr1;
case 562:
	if ( (*p) == 85 )
		goto tr755;
	goto tr1;
case 563:
	if ( (*p) == 69 )
		goto tr756;
	goto tr1;
case 564:
	if ( (*p) == 32 )
		goto tr757;
	goto tr1;
case 565:
	switch( (*p) ) {
		case 32: goto tr758;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr759;
case 566:
	switch( (*p) ) {
		case 32: goto tr760;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr761;
case 567:
	if ( (*p) == 32 )
		goto tr762;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr763;
	goto tr1;
case 568:
	if ( (*p) == 32 )
		goto tr764;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr765;
	goto tr1;
case 569:
	if ( (*p) == 32 )
		goto tr766;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr767;
	goto tr1;
case 570:
	switch( (*p) ) {
		case 10: goto tr768;
		case 13: goto tr769;
		case 32: goto tr770;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr771;
	goto tr1;
case 571:
	switch( (*p) ) {
		case 10: goto tr667;
		case 13: goto tr668;
	}
	goto tr1;
case 572:
	if ( (*p) == 10 )
		goto tr772;
	goto tr1;
case 573:
	if ( (*p) == 32 )
		goto tr773;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr774;
	goto tr1;
case 574:
	switch( (*p) ) {
		case 10: goto tr775;
		case 13: goto tr776;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr777;
	goto tr1;
case 575:
	if ( (*p) == 82 )
		goto tr778;
	goto tr1;
case 576:
	if ( (*p) == 83 )
		goto tr779;
	goto tr1;
case 577:
	if ( (*p) == 73 )
		goto tr780;
	goto tr1;
case 578:
	if ( (*p) == 79 )
		goto tr781;
	goto tr1;
case 579:
	if ( (*p) == 78 )
		goto tr782;
	goto tr1;
case 580:
	if ( (*p) == 32 )
		goto tr783;
	goto tr1;
case 581:
	switch( (*p) ) {
		case 10: goto tr785;
		case 13: goto tr786;
	}
	goto tr784;
case 582:
	switch( (*p) ) {
		case 10: goto tr788;
		case 13: goto tr789;
	}
	goto tr787;
case 583:
	switch( (*p) ) {
		case 97: goto tr790;
		case 99: goto tr791;
		case 100: goto tr792;
		case 101: goto tr793;
		case 102: goto tr794;
		case 103: goto tr795;
		case 105: goto tr796;
		case 108: goto tr797;
		case 109: goto tr798;
		case 112: goto tr799;
		case 113: goto tr800;
		case 114: goto tr801;
		case 115: goto tr802;
		case 118: goto tr803;
	}
	goto tr1;
case 584:
	switch( (*p) ) {
		case 100: goto tr804;
		case 112: goto tr805;
	}
	goto tr1;
case 585:
	switch( (*p) ) {
		case 100: goto tr806;
		case 109: goto tr807;
	}
	goto tr1;
case 586:
	if ( (*p) == 32 )
		goto tr808;
	goto tr1;
case 587:
	switch( (*p) ) {
		case 32: goto tr808;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr809;
case 588:
	switch( (*p) ) {
		case 32: goto tr810;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr811;
case 589:
	if ( (*p) == 32 )
		goto tr812;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr813;
	goto tr1;
case 590:
	if ( (*p) == 32 )
		goto tr814;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr815;
	goto tr1;
case 591:
	if ( (*p) == 32 )
		goto tr816;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr817;
	goto tr1;
case 592:
	if ( (*p) == 32 )
		goto tr818;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr819;
	goto tr1;
case 593:
	if ( (*p) == 32 )
		goto tr820;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr821;
	goto tr1;
case 594:
	switch( (*p) ) {
		case 10: goto tr822;
		case 13: goto tr823;
		case 32: goto tr824;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr825;
	goto tr1;
case 595:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
	}
	goto tr1;
case 750:
	goto tr1;
case 596:
	if ( (*p) == 10 )
		goto tr826;
	goto tr1;
case 597:
	if ( (*p) == 10 )
		goto tr828;
	goto tr1;
case 598:
	switch( (*p) ) {
		case 10: goto tr828;
		case 13: goto tr829;
		case 32: goto tr830;
		case 110: goto tr831;
	}
	goto tr1;
case 599:
	if ( (*p) == 111 )
		goto tr832;
	goto tr1;
case 600:
	if ( (*p) == 114 )
		goto tr833;
	goto tr1;
case 601:
	if ( (*p) == 101 )
		goto tr834;
	goto tr1;
case 602:
	if ( (*p) == 112 )
		goto tr835;
	goto tr1;
case 603:
	if ( (*p) == 108 )
		goto tr836;
	goto tr1;
case 604:
	if ( (*p) == 121 )
		goto tr837;
	goto tr1;
case 605:
	switch( (*p) ) {
		case 10: goto tr838;
		case 13: goto tr839;
		case 32: goto tr840;
	}
	goto tr1;
case 606:
	switch( (*p) ) {
		case 10: goto tr828;
		case 13: goto tr829;
		case 32: goto tr841;
	}
	goto tr1;
case 607:
	if ( (*p) == 105 )
		goto tr842;
	goto tr1;
case 608:
	if ( (*p) == 110 )
		goto tr843;
	goto tr1;
case 609:
	if ( (*p) == 32 )
		goto tr844;
	goto tr1;
case 610:
	if ( (*p) == 32 )
		goto tr845;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr846;
	goto tr1;
case 611:
	switch( (*p) ) {
		case 10: goto tr847;
		case 13: goto tr848;
		case 32: goto tr845;
	}
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr846;
	goto tr1;
case 612:
	switch( (*p) ) {
		case 10: goto tr847;
		case 13: goto tr848;
	}
	if ( 32 <= (*p) && (*p) <= 126 )
		goto tr849;
	goto tr1;
case 613:
	if ( (*p) == 112 )
		goto tr850;
	goto tr1;
case 614:
	if ( (*p) == 101 )
		goto tr851;
	goto tr1;
case 615:
	if ( (*p) == 110 )
		goto tr852;
	goto tr1;
case 616:
	if ( (*p) == 100 )
		goto tr853;
	goto tr1;
case 617:
	if ( (*p) == 97 )
		goto tr854;
	goto tr1;
case 618:
	if ( (*p) == 115 )
		goto tr855;
	goto tr1;
case 619:
	if ( (*p) == 32 )
		goto tr856;
	goto tr1;
case 620:
	switch( (*p) ) {
		case 32: goto tr857;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr858;
case 621:
	switch( (*p) ) {
		case 32: goto tr859;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr860;
case 622:
	if ( (*p) == 32 )
		goto tr861;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr862;
	goto tr1;
case 623:
	if ( (*p) == 32 )
		goto tr863;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr864;
	goto tr1;
case 624:
	if ( (*p) == 32 )
		goto tr865;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr866;
	goto tr1;
case 625:
	if ( (*p) == 32 )
		goto tr867;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr868;
	goto tr1;
case 626:
	if ( (*p) == 32 )
		goto tr869;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr870;
	goto tr1;
case 627:
	if ( (*p) == 32 )
		goto tr871;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr872;
	goto tr1;
case 628:
	if ( (*p) == 32 )
		goto tr873;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr874;
	goto tr1;
case 629:
	switch( (*p) ) {
		case 10: goto tr875;
		case 13: goto tr876;
		case 32: goto tr877;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr878;
	goto tr1;
case 630:
	if ( (*p) == 101 )
		goto tr879;
	goto tr1;
case 631:
	switch( (*p) ) {
		case 99: goto tr880;
		case 108: goto tr881;
	}
	goto tr1;
case 632:
	if ( (*p) == 114 )
		goto tr882;
	goto tr1;
case 633:
	if ( (*p) == 32 )
		goto tr883;
	goto tr1;
case 634:
	switch( (*p) ) {
		case 32: goto tr883;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr884;
case 635:
	switch( (*p) ) {
		case 32: goto tr885;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr886;
case 636:
	if ( (*p) == 32 )
		goto tr887;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr888;
	goto tr1;
case 637:
	switch( (*p) ) {
		case 10: goto tr889;
		case 13: goto tr890;
		case 32: goto tr891;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr892;
	goto tr1;
case 638:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr893;
		case 110: goto tr894;
	}
	goto tr1;
case 639:
	if ( (*p) == 111 )
		goto tr895;
	goto tr1;
case 640:
	if ( (*p) == 114 )
		goto tr896;
	goto tr1;
case 641:
	if ( (*p) == 101 )
		goto tr897;
	goto tr1;
case 642:
	if ( (*p) == 112 )
		goto tr898;
	goto tr1;
case 643:
	if ( (*p) == 108 )
		goto tr899;
	goto tr1;
case 644:
	if ( (*p) == 121 )
		goto tr900;
	goto tr1;
case 645:
	switch( (*p) ) {
		case 10: goto tr901;
		case 13: goto tr902;
		case 32: goto tr903;
	}
	goto tr1;
case 646:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr904;
	}
	goto tr1;
case 647:
	if ( (*p) == 101 )
		goto tr905;
	goto tr1;
case 648:
	if ( (*p) == 116 )
		goto tr906;
	goto tr1;
case 649:
	if ( (*p) == 101 )
		goto tr907;
	goto tr1;
case 650:
	if ( (*p) == 32 )
		goto tr908;
	goto tr1;
case 651:
	switch( (*p) ) {
		case 32: goto tr908;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr909;
case 652:
	switch( (*p) ) {
		case 10: goto tr910;
		case 13: goto tr911;
		case 32: goto tr912;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr913;
case 653:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr914;
		case 110: goto tr894;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr915;
	goto tr1;
case 654:
	switch( (*p) ) {
		case 10: goto tr916;
		case 13: goto tr917;
		case 32: goto tr918;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr919;
	goto tr1;
case 655:
	if ( (*p) == 120 )
		goto tr920;
	goto tr1;
case 656:
	if ( (*p) == 101 )
		goto tr921;
	goto tr1;
case 657:
	if ( (*p) == 99 )
		goto tr843;
	goto tr1;
case 658:
	if ( (*p) == 108 )
		goto tr922;
	goto tr1;
case 659:
	if ( (*p) == 117 )
		goto tr923;
	goto tr1;
case 660:
	if ( (*p) == 115 )
		goto tr924;
	goto tr1;
case 661:
	if ( (*p) == 104 )
		goto tr925;
	goto tr1;
case 662:
	if ( (*p) == 95 )
		goto tr926;
	goto tr1;
case 663:
	switch( (*p) ) {
		case 97: goto tr927;
		case 114: goto tr928;
	}
	goto tr1;
case 664:
	if ( (*p) == 108 )
		goto tr929;
	goto tr1;
case 665:
	if ( (*p) == 108 )
		goto tr930;
	goto tr1;
case 666:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr931;
	}
	goto tr1;
case 667:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr931;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr932;
	goto tr1;
case 668:
	switch( (*p) ) {
		case 10: goto tr933;
		case 13: goto tr934;
		case 32: goto tr935;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr936;
	goto tr1;
case 669:
	if ( (*p) == 101 )
		goto tr937;
	goto tr1;
case 670:
	if ( (*p) == 103 )
		goto tr938;
	goto tr1;
case 671:
	if ( (*p) == 101 )
		goto tr939;
	goto tr1;
case 672:
	if ( (*p) == 120 )
		goto tr940;
	goto tr1;
case 673:
	if ( (*p) == 32 )
		goto tr941;
	goto tr1;
case 674:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) <= 32 )
		goto tr1;
	goto tr942;
case 675:
	switch( (*p) ) {
		case 10: goto tr910;
		case 13: goto tr911;
		case 32: goto tr943;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr944;
case 676:
	if ( (*p) == 101 )
		goto tr945;
	goto tr1;
case 677:
	if ( (*p) == 116 )
		goto tr946;
	goto tr1;
case 678:
	switch( (*p) ) {
		case 32: goto tr947;
		case 115: goto tr948;
	}
	goto tr1;
case 679:
	switch( (*p) ) {
		case 32: goto tr947;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr949;
case 680:
	switch( (*p) ) {
		case 10: goto tr950;
		case 13: goto tr951;
		case 32: goto tr952;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr953;
case 681:
	switch( (*p) ) {
		case 10: goto tr954;
		case 13: goto tr955;
		case 32: goto tr956;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr949;
case 682:
	if ( (*p) == 32 )
		goto tr947;
	goto tr1;
case 683:
	if ( (*p) == 110 )
		goto tr957;
	goto tr1;
case 684:
	if ( (*p) == 99 )
		goto tr958;
	goto tr1;
case 685:
	if ( (*p) == 114 )
		goto tr959;
	goto tr1;
case 686:
	if ( (*p) == 101 )
		goto tr960;
	goto tr1;
case 687:
	if ( (*p) == 97 )
		goto tr961;
	goto tr1;
case 688:
	if ( (*p) == 115 )
		goto tr962;
	goto tr1;
case 689:
	if ( (*p) == 101 )
		goto tr963;
	goto tr1;
case 690:
	if ( (*p) == 45 )
		goto tr964;
	goto tr1;
case 691:
	switch( (*p) ) {
		case 103: goto tr965;
		case 115: goto tr966;
	}
	goto tr1;
case 692:
	if ( (*p) == 101 )
		goto tr967;
	goto tr1;
case 693:
	if ( (*p) == 116 )
		goto tr968;
	goto tr1;
case 694:
	if ( (*p) == 101 )
		goto tr969;
	goto tr1;
case 695:
	if ( (*p) == 116 )
		goto tr970;
	goto tr1;
case 696:
	if ( (*p) == 32 )
		goto tr971;
	goto tr1;
case 697:
	switch( (*p) ) {
		case 32: goto tr971;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr972;
case 698:
	switch( (*p) ) {
		case 32: goto tr973;
		case 127: goto tr1;
	}
	if ( (*p) <= 31 )
		goto tr1;
	goto tr974;
case 699:
	switch( (*p) ) {
		case 32: goto tr975;
		case 45: goto tr976;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr977;
	goto tr1;
case 700:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr978;
	goto tr1;
case 701:
	if ( (*p) == 32 )
		goto tr979;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr978;
	goto tr1;
case 702:
	if ( (*p) == 101 )
		goto tr980;
	goto tr1;
case 703:
	if ( (*p) == 116 )
		goto tr981;
	goto tr1;
case 704:
	if ( (*p) == 97 )
		goto tr982;
	goto tr1;
case 705:
	if ( (*p) == 103 )
		goto tr983;
	goto tr1;
case 706:
	if ( (*p) == 101 )
		goto tr984;
	goto tr1;
case 707:
	if ( (*p) == 116 )
		goto tr985;
	goto tr1;
case 708:
	if ( (*p) == 114 )
		goto tr986;
	goto tr1;
case 709:
	if ( (*p) == 101 )
		goto tr987;
	goto tr1;
case 710:
	if ( (*p) == 112 )
		goto tr988;
	goto tr1;
case 711:
	if ( (*p) == 101 )
		goto tr989;
	goto tr1;
case 712:
	if ( (*p) == 110 )
		goto tr990;
	goto tr1;
case 713:
	if ( (*p) == 100 )
		goto tr991;
	goto tr1;
case 714:
	if ( (*p) == 117 )
		goto tr992;
	goto tr1;
case 715:
	if ( (*p) == 105 )
		goto tr993;
	goto tr1;
case 716:
	if ( (*p) == 116 )
		goto tr994;
	goto tr1;
case 717:
	if ( (*p) == 101 )
		goto tr995;
	goto tr1;
case 718:
	if ( (*p) == 112 )
		goto tr996;
	goto tr1;
case 719:
	if ( (*p) == 108 )
		goto tr997;
	goto tr1;
case 720:
	if ( (*p) == 97 )
		goto tr998;
	goto tr1;
case 721:
	if ( (*p) == 99 )
		goto tr999;
	goto tr1;
case 722:
	if ( (*p) == 101 )
		goto tr1000;
	goto tr1;
case 723:
	switch( (*p) ) {
		case 101: goto tr1001;
		case 104: goto tr1002;
		case 116: goto tr1003;
	}
	goto tr1;
case 724:
	if ( (*p) == 116 )
		goto tr1004;
	goto tr1;
case 725:
	if ( (*p) == 117 )
		goto tr1005;
	goto tr1;
case 726:
	if ( (*p) == 116 )
		goto tr1006;
	goto tr1;
case 727:
	if ( (*p) == 100 )
		goto tr1007;
	goto tr1;
case 728:
	if ( (*p) == 111 )
		goto tr1008;
	goto tr1;
case 729:
	if ( (*p) == 119 )
		goto tr1009;
	goto tr1;
case 730:
	if ( (*p) == 110 )
		goto tr1010;
	goto tr1;
case 731:
	if ( (*p) == 97 )
		goto tr1011;
	goto tr1;
case 732:
	if ( (*p) == 116 )
		goto tr1012;
	goto tr1;
case 733:
	if ( (*p) == 115 )
		goto tr1013;
	goto tr1;
case 734:
	switch( (*p) ) {
		case 10: goto tr826;
		case 13: goto tr827;
		case 32: goto tr844;
	}
	goto tr1;
case 735:
	if ( (*p) == 101 )
		goto tr1014;
	goto tr1;
case 736:
	if ( (*p) == 114 )
		goto tr1015;
	goto tr1;
case 737:
	if ( (*p) == 115 )
		goto tr1016;
	goto tr1;
case 738:
	if ( (*p) == 105 )
		goto tr1017;
	goto tr1;
case 739:
	if ( (*p) == 111 )
		goto tr1018;
	goto tr1;
case 740:
	if ( (*p) == 110 )
		goto tr1019;
	goto tr1;
case 745:
	goto tr1;
	}

	tr1: cs = 0; goto _again;
	tr28: cs = 2; goto _again;
	tr0: cs = 2; goto f0;
	tr30: cs = 3; goto _again;
	tr26: cs = 3; goto f5;
	tr400: cs = 3; goto f13;
	tr423: cs = 3; goto f23;
	tr406: cs = 3; goto f24;
	tr292: cs = 3; goto f38;
	tr295: cs = 3; goto f40;
	tr392: cs = 3; goto f44;
	tr338: cs = 3; goto f47;
	tr380: cs = 3; goto f54;
	tr440: cs = 3; goto f65;
	tr444: cs = 3; goto f68;
	tr31: cs = 4; goto _again;
	tr27: cs = 4; goto f5;
	tr432: cs = 4; goto f13;
	tr424: cs = 4; goto f23;
	tr393: cs = 4; goto f44;
	tr483: cs = 4; goto f74;
	tr508: cs = 4; goto f79;
	tr2: cs = 5; goto _again;
	tr32: cs = 6; goto _again;
	tr33: cs = 7; goto _again;
	tr34: cs = 8; goto _again;
	tr35: cs = 9; goto _again;
	tr36: cs = 10; goto _again;
	tr37: cs = 11; goto _again;
	tr38: cs = 12; goto _again;
	tr39: cs = 13; goto _again;
	tr40: cs = 14; goto _again;
	tr41: cs = 15; goto _again;
	tr42: cs = 16; goto _again;
	tr46: cs = 17; goto _again;
	tr43: cs = 17; goto f0;
	tr47: cs = 18; goto _again;
	tr44: cs = 18; goto f0;
	tr45: cs = 19; goto f0;
	tr51: cs = 20; goto _again;
	tr49: cs = 20; goto f0;
	tr50: cs = 21; goto f8;
	tr52: cs = 22; goto f0;
	tr3: cs = 23; goto _again;
	tr53: cs = 24; goto _again;
	tr54: cs = 25; goto _again;
	tr55: cs = 26; goto _again;
	tr56: cs = 27; goto _again;
	tr57: cs = 28; goto _again;
	tr4: cs = 29; goto f1;
	tr59: cs = 30; goto _again;
	tr62: cs = 31; goto _again;
	tr240: cs = 31; goto f6;
	tr65: cs = 31; goto f10;
	tr69: cs = 31; goto f11;
	tr314: cs = 31; goto f16;
	tr318: cs = 31; goto f19;
	tr204: cs = 31; goto f28;
	tr205: cs = 31; goto f29;
	tr257: cs = 31; goto f35;
	tr328: cs = 31; goto f43;
	tr365: cs = 31; goto f50;
	tr60: cs = 32; goto _again;
	tr63: cs = 33; goto _again;
	tr64: cs = 34; goto _again;
	tr61: cs = 35; goto _again;
	tr66: cs = 36; goto _again;
	tr67: cs = 37; goto _again;
	tr68: cs = 38; goto _again;
	tr5: cs = 39; goto _again;
	tr70: cs = 40; goto _again;
	tr71: cs = 41; goto _again;
	tr72: cs = 42; goto _again;
	tr73: cs = 43; goto _again;
	tr74: cs = 44; goto _again;
	tr75: cs = 45; goto _again;
	tr78: cs = 46; goto _again;
	tr76: cs = 46; goto f12;
	tr79: cs = 47; goto _again;
	tr77: cs = 47; goto f13;
	tr80: cs = 48; goto f0;
	tr82: cs = 49; goto _again;
	tr81: cs = 49; goto f0;
	tr84: cs = 50; goto _again;
	tr83: cs = 50; goto f14;
	tr87: cs = 51; goto _again;
	tr85: cs = 51; goto f0;
	tr88: cs = 52; goto _again;
	tr86: cs = 52; goto f15;
	tr93: cs = 53; goto _again;
	tr89: cs = 53; goto f0;
	tr90: cs = 54; goto f16;
	tr97: cs = 54; goto f19;
	tr100: cs = 54; goto f20;
	tr173: cs = 55; goto _again;
	tr169: cs = 55; goto f15;
	tr94: cs = 55; goto f18;
	tr96: cs = 56; goto _again;
	tr95: cs = 57; goto _again;
	tr91: cs = 58; goto f17;
	tr101: cs = 58; goto f21;
	tr98: cs = 59; goto _again;
	tr92: cs = 59; goto f17;
	tr102: cs = 60; goto _again;
	tr99: cs = 60; goto f0;
	tr6: cs = 61; goto f2;
	tr103: cs = 62; goto _again;
	tr104: cs = 63; goto _again;
	tr105: cs = 64; goto _again;
	tr107: cs = 65; goto _again;
	tr106: cs = 65; goto f22;
	tr110: cs = 66; goto _again;
	tr108: cs = 66; goto f12;
	tr111: cs = 67; goto _again;
	tr109: cs = 67; goto f13;
	tr112: cs = 68; goto _again;
	tr113: cs = 69; goto _again;
	tr114: cs = 70; goto _again;
	tr115: cs = 71; goto _again;
	tr118: cs = 72; goto _again;
	tr116: cs = 72; goto f0;
	tr120: cs = 73; goto _again;
	tr119: cs = 73; goto f23;
	tr190: cs = 73; goto f26;
	tr121: cs = 74; goto _again;
	tr122: cs = 75; goto _again;
	tr123: cs = 76; goto _again;
	tr124: cs = 77; goto _again;
	tr125: cs = 78; goto _again;
	tr126: cs = 79; goto _again;
	tr127: cs = 80; goto _again;
	tr128: cs = 81; goto _again;
	tr130: cs = 82; goto _again;
	tr129: cs = 82; goto f0;
	tr132: cs = 83; goto _again;
	tr131: cs = 83; goto f24;
	tr133: cs = 84; goto _again;
	tr134: cs = 85; goto _again;
	tr135: cs = 86; goto _again;
	tr136: cs = 87; goto _again;
	tr137: cs = 88; goto _again;
	tr142: cs = 89; goto _again;
	tr138: cs = 89; goto f0;
	tr141: cs = 90; goto _again;
	tr145: cs = 91; goto _again;
	tr146: cs = 92; goto _again;
	tr148: cs = 93; goto _again;
	tr149: cs = 94; goto _again;
	tr151: cs = 95; goto _again;
	tr152: cs = 96; goto _again;
	tr153: cs = 97; goto _again;
	tr154: cs = 98; goto _again;
	tr144: cs = 98; goto f25;
	tr155: cs = 99; goto _again;
	tr156: cs = 100; goto _again;
	tr157: cs = 101; goto _again;
	tr158: cs = 102; goto _again;
	tr159: cs = 103; goto _again;
	tr160: cs = 104; goto _again;
	tr161: cs = 105; goto _again;
	tr162: cs = 106; goto _again;
	tr163: cs = 107; goto _again;
	tr164: cs = 108; goto _again;
	tr165: cs = 109; goto _again;
	tr166: cs = 110; goto _again;
	tr167: cs = 111; goto _again;
	tr172: cs = 112; goto _again;
	tr168: cs = 112; goto f0;
	tr174: cs = 113; goto _again;
	tr170: cs = 113; goto f15;
	tr175: cs = 114; goto _again;
	tr171: cs = 114; goto f15;
	tr150: cs = 115; goto _again;
	tr176: cs = 116; goto _again;
	tr147: cs = 117; goto _again;
	tr177: cs = 118; goto _again;
	tr143: cs = 119; goto _again;
	tr139: cs = 119; goto f0;
	tr140: cs = 120; goto _again;
	tr178: cs = 121; goto _again;
	tr179: cs = 122; goto _again;
	tr180: cs = 123; goto _again;
	tr181: cs = 124; goto _again;
	tr182: cs = 125; goto _again;
	tr183: cs = 126; goto _again;
	tr117: cs = 127; goto _again;
	tr184: cs = 128; goto _again;
	tr185: cs = 129; goto _again;
	tr186: cs = 130; goto _again;
	tr187: cs = 131; goto _again;
	tr188: cs = 132; goto _again;
	tr189: cs = 133; goto _again;
	tr7: cs = 134; goto _again;
	tr191: cs = 135; goto _again;
	tr192: cs = 136; goto _again;
	tr193: cs = 137; goto _again;
	tr194: cs = 138; goto _again;
	tr196: cs = 139; goto _again;
	tr197: cs = 140; goto _again;
	tr198: cs = 141; goto _again;
	tr195: cs = 142; goto _again;
	tr200: cs = 143; goto _again;
	tr201: cs = 144; goto _again;
	tr202: cs = 145; goto _again;
	tr203: cs = 146; goto _again;
	tr8: cs = 147; goto _again;
	tr9: cs = 148; goto _again;
	tr206: cs = 149; goto _again;
	tr208: cs = 150; goto _again;
	tr209: cs = 151; goto _again;
	tr210: cs = 152; goto _again;
	tr211: cs = 153; goto _again;
	tr212: cs = 154; goto _again;
	tr213: cs = 155; goto _again;
	tr214: cs = 156; goto _again;
	tr215: cs = 157; goto _again;
	tr216: cs = 158; goto _again;
	tr217: cs = 159; goto _again;
	tr221: cs = 160; goto _again;
	tr218: cs = 160; goto f0;
	tr222: cs = 161; goto _again;
	tr219: cs = 161; goto f0;
	tr220: cs = 162; goto f0;
	tr226: cs = 163; goto _again;
	tr224: cs = 163; goto f0;
	tr225: cs = 164; goto f8;
	tr227: cs = 165; goto f0;
	tr207: cs = 166; goto _again;
	tr228: cs = 167; goto _again;
	tr230: cs = 168; goto _again;
	tr232: cs = 169; goto _again;
	tr233: cs = 170; goto _again;
	tr234: cs = 171; goto _again;
	tr235: cs = 172; goto _again;
	tr236: cs = 173; goto _again;
	tr237: cs = 174; goto _again;
	tr238: cs = 175; goto _again;
	tr239: cs = 176; goto f31;
	tr241: cs = 177; goto _again;
	tr231: cs = 178; goto _again;
	tr242: cs = 179; goto f32;
	tr245: cs = 180; goto _again;
	tr243: cs = 180; goto f0;
	tr244: cs = 181; goto f33;
	tr246: cs = 182; goto f0;
	tr253: cs = 183; goto _again;
	tr248: cs = 183; goto f34;
	tr250: cs = 184; goto _again;
	tr251: cs = 185; goto _again;
	tr252: cs = 186; goto _again;
	tr249: cs = 187; goto f34;
	tr254: cs = 188; goto _again;
	tr247: cs = 188; goto f0;
	tr229: cs = 189; goto _again;
	tr255: cs = 190; goto _again;
	tr256: cs = 191; goto _again;
	tr10: cs = 192; goto f3;
	tr258: cs = 193; goto _again;
	tr260: cs = 194; goto _again;
	tr261: cs = 195; goto _again;
	tr262: cs = 196; goto _again;
	tr264: cs = 197; goto _again;
	tr263: cs = 197; goto f36;
	tr267: cs = 198; goto _again;
	tr265: cs = 198; goto f12;
	tr268: cs = 199; goto _again;
	tr266: cs = 199; goto f13;
	tr271: cs = 200; goto _again;
	tr269: cs = 200; goto f0;
	tr272: cs = 201; goto _again;
	tr270: cs = 201; goto f15;
	tr277: cs = 202; goto _again;
	tr273: cs = 202; goto f0;
	tr274: cs = 203; goto f16;
	tr278: cs = 203; goto f19;
	tr281: cs = 203; goto f20;
	tr275: cs = 204; goto f17;
	tr282: cs = 204; goto f21;
	tr279: cs = 205; goto _again;
	tr276: cs = 205; goto f17;
	tr283: cs = 206; goto _again;
	tr280: cs = 206; goto f0;
	tr259: cs = 207; goto _again;
	tr284: cs = 208; goto _again;
	tr285: cs = 209; goto _again;
	tr286: cs = 210; goto _again;
	tr287: cs = 211; goto _again;
	tr288: cs = 212; goto _again;
	tr289: cs = 213; goto _again;
	tr293: cs = 214; goto _again;
	tr290: cs = 214; goto f0;
	tr11: cs = 215; goto _again;
	tr296: cs = 216; goto _again;
	tr298: cs = 217; goto f41;
	tr343: cs = 217; goto f48;
	tr480: cs = 217; goto f73;
	tr489: cs = 217; goto f75;
	tr493: cs = 217; goto f76;
	tr300: cs = 218; goto _again;
	tr303: cs = 219; goto _again;
	tr301: cs = 219; goto f42;
	tr304: cs = 220; goto _again;
	tr302: cs = 220; goto f13;
	tr468: cs = 220; goto f14;
	tr307: cs = 221; goto _again;
	tr305: cs = 221; goto f0;
	tr308: cs = 222; goto _again;
	tr306: cs = 222; goto f15;
	tr311: cs = 223; goto _again;
	tr309: cs = 223; goto f0;
	tr312: cs = 224; goto _again;
	tr310: cs = 224; goto f24;
	tr317: cs = 225; goto _again;
	tr313: cs = 225; goto f0;
	tr319: cs = 226; goto _again;
	tr315: cs = 226; goto f17;
	tr329: cs = 226; goto f44;
	tr366: cs = 226; goto f51;
	tr320: cs = 227; goto _again;
	tr316: cs = 227; goto f17;
	tr321: cs = 228; goto _again;
	tr322: cs = 229; goto _again;
	tr323: cs = 230; goto _again;
	tr324: cs = 231; goto _again;
	tr325: cs = 232; goto _again;
	tr326: cs = 233; goto _again;
	tr327: cs = 234; goto _again;
	tr331: cs = 235; goto _again;
	tr330: cs = 235; goto f44;
	tr367: cs = 235; goto f51;
	tr299: cs = 236; goto _again;
	tr332: cs = 237; goto _again;
	tr333: cs = 238; goto f45;
	tr334: cs = 239; goto _again;
	tr335: cs = 240; goto f0;
	tr339: cs = 241; goto _again;
	tr336: cs = 241; goto f0;
	tr297: cs = 242; goto _again;
	tr340: cs = 243; goto _again;
	tr341: cs = 244; goto _again;
	tr342: cs = 245; goto _again;
	tr12: cs = 246; goto _again;
	tr344: cs = 247; goto _again;
	tr345: cs = 248; goto _again;
	tr347: cs = 249; goto _again;
	tr346: cs = 249; goto f49;
	tr350: cs = 250; goto _again;
	tr348: cs = 250; goto f42;
	tr351: cs = 251; goto _again;
	tr349: cs = 251; goto f13;
	tr354: cs = 252; goto _again;
	tr352: cs = 252; goto f0;
	tr355: cs = 253; goto _again;
	tr353: cs = 253; goto f15;
	tr358: cs = 254; goto _again;
	tr356: cs = 254; goto f0;
	tr359: cs = 255; goto _again;
	tr357: cs = 255; goto f24;
	tr362: cs = 256; goto _again;
	tr360: cs = 256; goto f0;
	tr363: cs = 257; goto _again;
	tr361: cs = 257; goto f17;
	tr368: cs = 258; goto _again;
	tr364: cs = 258; goto f0;
	tr13: cs = 259; goto _again;
	tr369: cs = 260; goto _again;
	tr370: cs = 261; goto _again;
	tr372: cs = 262; goto f52;
	tr448: cs = 262; goto f69;
	tr373: cs = 263; goto _again;
	tr376: cs = 264; goto _again;
	tr374: cs = 264; goto f42;
	tr377: cs = 265; goto _again;
	tr375: cs = 265; goto f13;
	tr382: cs = 266; goto _again;
	tr378: cs = 266; goto f0;
	tr383: cs = 267; goto _again;
	tr407: cs = 267; goto f24;
	tr381: cs = 267; goto f54;
	tr384: cs = 268; goto _again;
	tr385: cs = 269; goto _again;
	tr386: cs = 270; goto _again;
	tr387: cs = 271; goto _again;
	tr388: cs = 272; goto _again;
	tr389: cs = 273; goto _again;
	tr390: cs = 274; goto _again;
	tr371: cs = 275; goto _again;
	tr394: cs = 276; goto _again;
	tr395: cs = 277; goto _again;
	tr396: cs = 278; goto f56;
	tr397: cs = 279; goto _again;
	tr402: cs = 280; goto _again;
	tr398: cs = 280; goto f42;
	tr403: cs = 281; goto _again;
	tr401: cs = 281; goto f13;
	tr408: cs = 282; goto _again;
	tr404: cs = 282; goto f0;
	tr14: cs = 283; goto _again;
	tr409: cs = 284; goto _again;
	tr410: cs = 285; goto _again;
	tr15: cs = 286; goto _again;
	tr411: cs = 287; goto _again;
	tr412: cs = 288; goto _again;
	tr413: cs = 289; goto _again;
	tr414: cs = 290; goto _again;
	tr415: cs = 291; goto _again;
	tr416: cs = 292; goto _again;
	tr418: cs = 293; goto _again;
	tr419: cs = 294; goto f59;
	tr499: cs = 294; goto f77;
	tr420: cs = 295; goto _again;
	tr425: cs = 296; goto _again;
	tr421: cs = 296; goto f0;
	tr417: cs = 297; goto _again;
	tr426: cs = 298; goto _again;
	tr427: cs = 299; goto _again;
	tr428: cs = 300; goto _again;
	tr429: cs = 301; goto f61;
	tr430: cs = 302; goto _again;
	tr433: cs = 303; goto _again;
	tr431: cs = 303; goto f42;
	tr16: cs = 304; goto _again;
	tr434: cs = 305; goto _again;
	tr435: cs = 306; goto f62;
	tr436: cs = 307; goto _again;
	tr442: cs = 308; goto _again;
	tr438: cs = 308; goto f42;
	tr445: cs = 309; goto _again;
	tr441: cs = 309; goto f66;
	tr437: cs = 310; goto f63;
	tr457: cs = 310; goto f70;
	tr474: cs = 310; goto f72;
	tr17: cs = 311; goto _again;
	tr446: cs = 312; goto _again;
	tr447: cs = 313; goto _again;
	tr18: cs = 314; goto _again;
	tr449: cs = 315; goto _again;
	tr450: cs = 316; goto _again;
	tr451: cs = 317; goto _again;
	tr452: cs = 318; goto _again;
	tr453: cs = 319; goto _again;
	tr454: cs = 320; goto _again;
	tr456: cs = 321; goto _again;
	tr455: cs = 322; goto _again;
	tr458: cs = 323; goto _again;
	tr459: cs = 324; goto f71;
	tr460: cs = 325; goto _again;
	tr463: cs = 326; goto _again;
	tr461: cs = 326; goto f42;
	tr464: cs = 327; goto _again;
	tr462: cs = 327; goto f13;
	tr465: cs = 328; goto f0;
	tr467: cs = 329; goto _again;
	tr466: cs = 329; goto f0;
	tr19: cs = 330; goto _again;
	tr469: cs = 331; goto _again;
	tr470: cs = 332; goto _again;
	tr471: cs = 333; goto _again;
	tr472: cs = 334; goto _again;
	tr473: cs = 335; goto _again;
	tr20: cs = 336; goto _again;
	tr475: cs = 337; goto _again;
	tr476: cs = 338; goto _again;
	tr477: cs = 339; goto _again;
	tr478: cs = 340; goto _again;
	tr479: cs = 341; goto _again;
	tr21: cs = 342; goto _again;
	tr481: cs = 343; goto _again;
	tr482: cs = 344; goto _again;
	tr22: cs = 345; goto _again;
	tr484: cs = 346; goto _again;
	tr485: cs = 347; goto _again;
	tr486: cs = 348; goto _again;
	tr487: cs = 349; goto _again;
	tr488: cs = 350; goto _again;
	tr23: cs = 351; goto _again;
	tr490: cs = 352; goto _again;
	tr491: cs = 353; goto _again;
	tr494: cs = 354; goto _again;
	tr495: cs = 355; goto _again;
	tr496: cs = 356; goto _again;
	tr497: cs = 357; goto _again;
	tr498: cs = 358; goto _again;
	tr492: cs = 359; goto _again;
	tr500: cs = 360; goto _again;
	tr501: cs = 361; goto _again;
	tr502: cs = 362; goto f78;
	tr24: cs = 363; goto _again;
	tr503: cs = 364; goto _again;
	tr504: cs = 365; goto _again;
	tr505: cs = 366; goto _again;
	tr506: cs = 367; goto _again;
	tr507: cs = 368; goto _again;
	tr522: cs = 370; goto _again;
	tr509: cs = 370; goto f0;
	tr524: cs = 371; goto _again;
	tr520: cs = 371; goto f5;
	tr786: cs = 371; goto f38;
	tr789: cs = 371; goto f40;
	tr525: cs = 372; goto _again;
	tr521: cs = 372; goto f5;
	tr510: cs = 373; goto _again;
	tr526: cs = 374; goto _again;
	tr527: cs = 375; goto _again;
	tr528: cs = 376; goto _again;
	tr529: cs = 377; goto _again;
	tr530: cs = 378; goto _again;
	tr531: cs = 379; goto _again;
	tr532: cs = 380; goto _again;
	tr533: cs = 381; goto _again;
	tr534: cs = 382; goto _again;
	tr535: cs = 383; goto _again;
	tr536: cs = 384; goto _again;
	tr540: cs = 385; goto _again;
	tr537: cs = 385; goto f0;
	tr541: cs = 386; goto _again;
	tr538: cs = 386; goto f0;
	tr539: cs = 387; goto f0;
	tr545: cs = 388; goto _again;
	tr543: cs = 388; goto f0;
	tr544: cs = 389; goto f8;
	tr546: cs = 390; goto f0;
	tr511: cs = 391; goto _again;
	tr547: cs = 392; goto _again;
	tr548: cs = 393; goto _again;
	tr549: cs = 394; goto _again;
	tr550: cs = 395; goto _again;
	tr551: cs = 396; goto _again;
	tr512: cs = 397; goto f1;
	tr553: cs = 398; goto _again;
	tr556: cs = 399; goto _again;
	tr734: cs = 399; goto f6;
	tr559: cs = 399; goto f10;
	tr563: cs = 399; goto f11;
	tr698: cs = 399; goto f28;
	tr699: cs = 399; goto f29;
	tr751: cs = 399; goto f35;
	tr554: cs = 400; goto _again;
	tr557: cs = 401; goto _again;
	tr558: cs = 402; goto _again;
	tr555: cs = 403; goto _again;
	tr560: cs = 404; goto _again;
	tr561: cs = 405; goto _again;
	tr562: cs = 406; goto _again;
	tr513: cs = 407; goto _again;
	tr564: cs = 408; goto _again;
	tr565: cs = 409; goto _again;
	tr566: cs = 410; goto _again;
	tr567: cs = 411; goto _again;
	tr568: cs = 412; goto _again;
	tr569: cs = 413; goto _again;
	tr572: cs = 414; goto _again;
	tr570: cs = 414; goto f12;
	tr573: cs = 415; goto _again;
	tr571: cs = 415; goto f13;
	tr574: cs = 416; goto f0;
	tr576: cs = 417; goto _again;
	tr575: cs = 417; goto f0;
	tr578: cs = 418; goto _again;
	tr577: cs = 418; goto f14;
	tr581: cs = 419; goto _again;
	tr579: cs = 419; goto f0;
	tr582: cs = 420; goto _again;
	tr580: cs = 420; goto f15;
	tr587: cs = 421; goto _again;
	tr583: cs = 421; goto f0;
	tr584: cs = 422; goto f16;
	tr591: cs = 422; goto f19;
	tr594: cs = 422; goto f20;
	tr667: cs = 423; goto _again;
	tr663: cs = 423; goto f15;
	tr588: cs = 423; goto f18;
	tr590: cs = 424; goto _again;
	tr589: cs = 425; goto _again;
	tr585: cs = 426; goto f17;
	tr595: cs = 426; goto f21;
	tr592: cs = 427; goto _again;
	tr586: cs = 427; goto f17;
	tr596: cs = 428; goto _again;
	tr593: cs = 428; goto f0;
	tr514: cs = 429; goto f2;
	tr597: cs = 430; goto _again;
	tr598: cs = 431; goto _again;
	tr599: cs = 432; goto _again;
	tr601: cs = 433; goto _again;
	tr600: cs = 433; goto f22;
	tr604: cs = 434; goto _again;
	tr602: cs = 434; goto f12;
	tr605: cs = 435; goto _again;
	tr603: cs = 435; goto f13;
	tr606: cs = 436; goto _again;
	tr607: cs = 437; goto _again;
	tr608: cs = 438; goto _again;
	tr609: cs = 439; goto _again;
	tr612: cs = 440; goto _again;
	tr610: cs = 440; goto f0;
	tr614: cs = 441; goto _again;
	tr613: cs = 441; goto f23;
	tr684: cs = 441; goto f26;
	tr615: cs = 442; goto _again;
	tr616: cs = 443; goto _again;
	tr617: cs = 444; goto _again;
	tr618: cs = 445; goto _again;
	tr619: cs = 446; goto _again;
	tr620: cs = 447; goto _again;
	tr621: cs = 448; goto _again;
	tr622: cs = 449; goto _again;
	tr624: cs = 450; goto _again;
	tr623: cs = 450; goto f0;
	tr626: cs = 451; goto _again;
	tr625: cs = 451; goto f24;
	tr627: cs = 452; goto _again;
	tr628: cs = 453; goto _again;
	tr629: cs = 454; goto _again;
	tr630: cs = 455; goto _again;
	tr631: cs = 456; goto _again;
	tr636: cs = 457; goto _again;
	tr632: cs = 457; goto f0;
	tr635: cs = 458; goto _again;
	tr639: cs = 459; goto _again;
	tr640: cs = 460; goto _again;
	tr642: cs = 461; goto _again;
	tr643: cs = 462; goto _again;
	tr645: cs = 463; goto _again;
	tr646: cs = 464; goto _again;
	tr647: cs = 465; goto _again;
	tr648: cs = 466; goto _again;
	tr638: cs = 466; goto f25;
	tr649: cs = 467; goto _again;
	tr650: cs = 468; goto _again;
	tr651: cs = 469; goto _again;
	tr652: cs = 470; goto _again;
	tr653: cs = 471; goto _again;
	tr654: cs = 472; goto _again;
	tr655: cs = 473; goto _again;
	tr656: cs = 474; goto _again;
	tr657: cs = 475; goto _again;
	tr658: cs = 476; goto _again;
	tr659: cs = 477; goto _again;
	tr660: cs = 478; goto _again;
	tr661: cs = 479; goto _again;
	tr666: cs = 480; goto _again;
	tr662: cs = 480; goto f0;
	tr668: cs = 481; goto _again;
	tr664: cs = 481; goto f15;
	tr669: cs = 482; goto _again;
	tr665: cs = 482; goto f15;
	tr644: cs = 483; goto _again;
	tr670: cs = 484; goto _again;
	tr641: cs = 485; goto _again;
	tr671: cs = 486; goto _again;
	tr637: cs = 487; goto _again;
	tr633: cs = 487; goto f0;
	tr634: cs = 488; goto _again;
	tr672: cs = 489; goto _again;
	tr673: cs = 490; goto _again;
	tr674: cs = 491; goto _again;
	tr675: cs = 492; goto _again;
	tr676: cs = 493; goto _again;
	tr677: cs = 494; goto _again;
	tr611: cs = 495; goto _again;
	tr678: cs = 496; goto _again;
	tr679: cs = 497; goto _again;
	tr680: cs = 498; goto _again;
	tr681: cs = 499; goto _again;
	tr682: cs = 500; goto _again;
	tr683: cs = 501; goto _again;
	tr515: cs = 502; goto _again;
	tr685: cs = 503; goto _again;
	tr686: cs = 504; goto _again;
	tr687: cs = 505; goto _again;
	tr688: cs = 506; goto _again;
	tr690: cs = 507; goto _again;
	tr691: cs = 508; goto _again;
	tr692: cs = 509; goto _again;
	tr689: cs = 510; goto _again;
	tr694: cs = 511; goto _again;
	tr695: cs = 512; goto _again;
	tr696: cs = 513; goto _again;
	tr697: cs = 514; goto _again;
	tr516: cs = 515; goto _again;
	tr517: cs = 516; goto _again;
	tr700: cs = 517; goto _again;
	tr702: cs = 518; goto _again;
	tr703: cs = 519; goto _again;
	tr704: cs = 520; goto _again;
	tr705: cs = 521; goto _again;
	tr706: cs = 522; goto _again;
	tr707: cs = 523; goto _again;
	tr708: cs = 524; goto _again;
	tr709: cs = 525; goto _again;
	tr710: cs = 526; goto _again;
	tr711: cs = 527; goto _again;
	tr715: cs = 528; goto _again;
	tr712: cs = 528; goto f0;
	tr716: cs = 529; goto _again;
	tr713: cs = 529; goto f0;
	tr714: cs = 530; goto f0;
	tr720: cs = 531; goto _again;
	tr718: cs = 531; goto f0;
	tr719: cs = 532; goto f8;
	tr721: cs = 533; goto f0;
	tr701: cs = 534; goto _again;
	tr722: cs = 535; goto _again;
	tr724: cs = 536; goto _again;
	tr726: cs = 537; goto _again;
	tr727: cs = 538; goto _again;
	tr728: cs = 539; goto _again;
	tr729: cs = 540; goto _again;
	tr730: cs = 541; goto _again;
	tr731: cs = 542; goto _again;
	tr732: cs = 543; goto _again;
	tr733: cs = 544; goto f31;
	tr735: cs = 545; goto _again;
	tr725: cs = 546; goto _again;
	tr736: cs = 547; goto f32;
	tr739: cs = 548; goto _again;
	tr737: cs = 548; goto f0;
	tr738: cs = 549; goto f33;
	tr740: cs = 550; goto f0;
	tr747: cs = 551; goto _again;
	tr742: cs = 551; goto f34;
	tr744: cs = 552; goto _again;
	tr745: cs = 553; goto _again;
	tr746: cs = 554; goto _again;
	tr743: cs = 555; goto f34;
	tr748: cs = 556; goto _again;
	tr741: cs = 556; goto f0;
	tr723: cs = 557; goto _again;
	tr749: cs = 558; goto _again;
	tr750: cs = 559; goto _again;
	tr518: cs = 560; goto f3;
	tr752: cs = 561; goto _again;
	tr754: cs = 562; goto _again;
	tr755: cs = 563; goto _again;
	tr756: cs = 564; goto _again;
	tr758: cs = 565; goto _again;
	tr757: cs = 565; goto f36;
	tr761: cs = 566; goto _again;
	tr759: cs = 566; goto f12;
	tr762: cs = 567; goto _again;
	tr760: cs = 567; goto f13;
	tr765: cs = 568; goto _again;
	tr763: cs = 568; goto f0;
	tr766: cs = 569; goto _again;
	tr764: cs = 569; goto f15;
	tr771: cs = 570; goto _again;
	tr767: cs = 570; goto f0;
	tr768: cs = 571; goto f16;
	tr772: cs = 571; goto f19;
	tr775: cs = 571; goto f20;
	tr769: cs = 572; goto f17;
	tr776: cs = 572; goto f21;
	tr773: cs = 573; goto _again;
	tr770: cs = 573; goto f17;
	tr777: cs = 574; goto _again;
	tr774: cs = 574; goto f0;
	tr753: cs = 575; goto _again;
	tr778: cs = 576; goto _again;
	tr779: cs = 577; goto _again;
	tr780: cs = 578; goto _again;
	tr781: cs = 579; goto _again;
	tr782: cs = 580; goto _again;
	tr783: cs = 581; goto _again;
	tr787: cs = 582; goto _again;
	tr784: cs = 582; goto f0;
	tr790: cs = 584; goto _again;
	tr804: cs = 585; goto _again;
	tr806: cs = 586; goto f41;
	tr853: cs = 586; goto f48;
	tr991: cs = 586; goto f73;
	tr1000: cs = 586; goto f75;
	tr1004: cs = 586; goto f76;
	tr808: cs = 587; goto _again;
	tr811: cs = 588; goto _again;
	tr809: cs = 588; goto f42;
	tr812: cs = 589; goto _again;
	tr810: cs = 589; goto f13;
	tr979: cs = 589; goto f14;
	tr815: cs = 590; goto _again;
	tr813: cs = 590; goto f0;
	tr816: cs = 591; goto _again;
	tr814: cs = 591; goto f15;
	tr819: cs = 592; goto _again;
	tr817: cs = 592; goto f0;
	tr820: cs = 593; goto _again;
	tr818: cs = 593; goto f24;
	tr825: cs = 594; goto _again;
	tr821: cs = 594; goto f0;
	tr822: cs = 595; goto f16;
	tr828: cs = 595; goto f19;
	tr838: cs = 595; goto f43;
	tr875: cs = 595; goto f50;
	tr827: cs = 596; goto _again;
	tr911: cs = 596; goto f13;
	tr934: cs = 596; goto f23;
	tr917: cs = 596; goto f24;
	tr902: cs = 596; goto f44;
	tr848: cs = 596; goto f47;
	tr890: cs = 596; goto f54;
	tr951: cs = 596; goto f65;
	tr955: cs = 596; goto f68;
	tr829: cs = 597; goto _again;
	tr823: cs = 597; goto f17;
	tr839: cs = 597; goto f44;
	tr876: cs = 597; goto f51;
	tr830: cs = 598; goto _again;
	tr824: cs = 598; goto f17;
	tr831: cs = 599; goto _again;
	tr832: cs = 600; goto _again;
	tr833: cs = 601; goto _again;
	tr834: cs = 602; goto _again;
	tr835: cs = 603; goto _again;
	tr836: cs = 604; goto _again;
	tr837: cs = 605; goto _again;
	tr841: cs = 606; goto _again;
	tr840: cs = 606; goto f44;
	tr877: cs = 606; goto f51;
	tr807: cs = 607; goto _again;
	tr842: cs = 608; goto _again;
	tr843: cs = 609; goto f45;
	tr844: cs = 610; goto _again;
	tr845: cs = 611; goto f0;
	tr849: cs = 612; goto _again;
	tr846: cs = 612; goto f0;
	tr805: cs = 613; goto _again;
	tr850: cs = 614; goto _again;
	tr851: cs = 615; goto _again;
	tr852: cs = 616; goto _again;
	tr791: cs = 617; goto _again;
	tr854: cs = 618; goto _again;
	tr855: cs = 619; goto _again;
	tr857: cs = 620; goto _again;
	tr856: cs = 620; goto f49;
	tr860: cs = 621; goto _again;
	tr858: cs = 621; goto f42;
	tr861: cs = 622; goto _again;
	tr859: cs = 622; goto f13;
	tr864: cs = 623; goto _again;
	tr862: cs = 623; goto f0;
	tr865: cs = 624; goto _again;
	tr863: cs = 624; goto f15;
	tr868: cs = 625; goto _again;
	tr866: cs = 625; goto f0;
	tr869: cs = 626; goto _again;
	tr867: cs = 626; goto f24;
	tr872: cs = 627; goto _again;
	tr870: cs = 627; goto f0;
	tr873: cs = 628; goto _again;
	tr871: cs = 628; goto f17;
	tr878: cs = 629; goto _again;
	tr874: cs = 629; goto f0;
	tr792: cs = 630; goto _again;
	tr879: cs = 631; goto _again;
	tr880: cs = 632; goto _again;
	tr882: cs = 633; goto f52;
	tr959: cs = 633; goto f69;
	tr883: cs = 634; goto _again;
	tr886: cs = 635; goto _again;
	tr884: cs = 635; goto f42;
	tr887: cs = 636; goto _again;
	tr885: cs = 636; goto f13;
	tr892: cs = 637; goto _again;
	tr888: cs = 637; goto f0;
	tr893: cs = 638; goto _again;
	tr918: cs = 638; goto f24;
	tr891: cs = 638; goto f54;
	tr894: cs = 639; goto _again;
	tr895: cs = 640; goto _again;
	tr896: cs = 641; goto _again;
	tr897: cs = 642; goto _again;
	tr898: cs = 643; goto _again;
	tr899: cs = 644; goto _again;
	tr900: cs = 645; goto _again;
	tr904: cs = 646; goto _again;
	tr943: cs = 646; goto f13;
	tr935: cs = 646; goto f23;
	tr903: cs = 646; goto f44;
	tr994: cs = 646; goto f74;
	tr1019: cs = 646; goto f79;
	tr881: cs = 647; goto _again;
	tr905: cs = 648; goto _again;
	tr906: cs = 649; goto _again;
	tr907: cs = 650; goto f56;
	tr908: cs = 651; goto _again;
	tr913: cs = 652; goto _again;
	tr909: cs = 652; goto f42;
	tr914: cs = 653; goto _again;
	tr912: cs = 653; goto f13;
	tr919: cs = 654; goto _again;
	tr915: cs = 654; goto f0;
	tr793: cs = 655; goto _again;
	tr920: cs = 656; goto _again;
	tr921: cs = 657; goto _again;
	tr794: cs = 658; goto _again;
	tr922: cs = 659; goto _again;
	tr923: cs = 660; goto _again;
	tr924: cs = 661; goto _again;
	tr925: cs = 662; goto _again;
	tr926: cs = 663; goto _again;
	tr927: cs = 664; goto _again;
	tr929: cs = 665; goto _again;
	tr930: cs = 666; goto f59;
	tr1010: cs = 666; goto f77;
	tr931: cs = 667; goto _again;
	tr936: cs = 668; goto _again;
	tr932: cs = 668; goto f0;
	tr928: cs = 669; goto _again;
	tr937: cs = 670; goto _again;
	tr938: cs = 671; goto _again;
	tr939: cs = 672; goto _again;
	tr940: cs = 673; goto f61;
	tr941: cs = 674; goto _again;
	tr944: cs = 675; goto _again;
	tr942: cs = 675; goto f42;
	tr795: cs = 676; goto _again;
	tr945: cs = 677; goto _again;
	tr946: cs = 678; goto f62;
	tr947: cs = 679; goto _again;
	tr953: cs = 680; goto _again;
	tr949: cs = 680; goto f42;
	tr956: cs = 681; goto _again;
	tr952: cs = 681; goto f66;
	tr948: cs = 682; goto f63;
	tr968: cs = 682; goto f70;
	tr985: cs = 682; goto f72;
	tr796: cs = 683; goto _again;
	tr957: cs = 684; goto _again;
	tr958: cs = 685; goto _again;
	tr797: cs = 686; goto _again;
	tr960: cs = 687; goto _again;
	tr961: cs = 688; goto _again;
	tr962: cs = 689; goto _again;
	tr963: cs = 690; goto _again;
	tr964: cs = 691; goto _again;
	tr965: cs = 692; goto _again;
	tr967: cs = 693; goto _again;
	tr966: cs = 694; goto _again;
	tr969: cs = 695; goto _again;
	tr970: cs = 696; goto f71;
	tr971: cs = 697; goto _again;
	tr974: cs = 698; goto _again;
	tr972: cs = 698; goto f42;
	tr975: cs = 699; goto _again;
	tr973: cs = 699; goto f13;
	tr976: cs = 700; goto f0;
	tr978: cs = 701; goto _again;
	tr977: cs = 701; goto f0;
	tr798: cs = 702; goto _again;
	tr980: cs = 703; goto _again;
	tr981: cs = 704; goto _again;
	tr982: cs = 705; goto _again;
	tr983: cs = 706; goto _again;
	tr984: cs = 707; goto _again;
	tr799: cs = 708; goto _again;
	tr986: cs = 709; goto _again;
	tr987: cs = 710; goto _again;
	tr988: cs = 711; goto _again;
	tr989: cs = 712; goto _again;
	tr990: cs = 713; goto _again;
	tr800: cs = 714; goto _again;
	tr992: cs = 715; goto _again;
	tr993: cs = 716; goto _again;
	tr801: cs = 717; goto _again;
	tr995: cs = 718; goto _again;
	tr996: cs = 719; goto _again;
	tr997: cs = 720; goto _again;
	tr998: cs = 721; goto _again;
	tr999: cs = 722; goto _again;
	tr802: cs = 723; goto _again;
	tr1001: cs = 724; goto _again;
	tr1002: cs = 725; goto _again;
	tr1005: cs = 726; goto _again;
	tr1006: cs = 727; goto _again;
	tr1007: cs = 728; goto _again;
	tr1008: cs = 729; goto _again;
	tr1009: cs = 730; goto _again;
	tr1003: cs = 731; goto _again;
	tr1011: cs = 732; goto _again;
	tr1012: cs = 733; goto _again;
	tr1013: cs = 734; goto f78;
	tr803: cs = 735; goto _again;
	tr1014: cs = 736; goto _again;
	tr1015: cs = 737; goto _again;
	tr1016: cs = 738; goto _again;
	tr1017: cs = 739; goto _again;
	tr1018: cs = 740; goto _again;
	tr25: cs = 741; goto f4;
	tr29: cs = 741; goto f6;
	tr291: cs = 741; goto f37;
	tr294: cs = 741; goto f39;
	tr337: cs = 741; goto f46;
	tr379: cs = 741; goto f53;
	tr391: cs = 741; goto f55;
	tr399: cs = 741; goto f57;
	tr405: cs = 741; goto f58;
	tr422: cs = 741; goto f60;
	tr439: cs = 741; goto f64;
	tr443: cs = 741; goto f67;
	tr48: cs = 742; goto f7;
	tr58: cs = 743; goto f9;
	tr199: cs = 743; goto f27;
	tr223: cs = 744; goto f30;
	tr519: cs = 746; goto f4;
	tr523: cs = 746; goto f6;
	tr785: cs = 746; goto f37;
	tr788: cs = 746; goto f39;
	tr542: cs = 747; goto f7;
	tr552: cs = 748; goto f9;
	tr693: cs = 748; goto f27;
	tr717: cs = 749; goto f30;
	tr826: cs = 750; goto f6;
	tr847: cs = 750; goto f46;
	tr889: cs = 750; goto f53;
	tr901: cs = 750; goto f55;
	tr910: cs = 750; goto f57;
	tr916: cs = 750; goto f58;
	tr933: cs = 750; goto f60;
	tr950: cs = 750; goto f64;
	tr954: cs = 750; goto f67;

f0:
#line 31 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    parser->partial_token = 1;
    parser->te = parser->tbuf;
    ts = p;
  }
}
	goto _again;
f6:
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f8:
#line 133 "mcrouter/lib/mc/ascii_client.rl"
	{
    parser->msg->err_code = strtoll(ts, NULL, 10);
  }
	goto _again;
f10:
#line 186 "mcrouter/lib/mc/ascii_client.rl"
	{
    parser->msg->result = mc_res_local_error;
    parser->msg->value.str = "unexpected ERROR reply";
    parser->msg->value.len = strlen(parser->msg->value.str);
    dbg_error("%s", parser->msg->value.str);
    isError = true;
  }
	goto _again;
f35:
#line 215 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_stored; }
	goto _again;
f31:
#line 216 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->result = mc_res_stalestored;
}
	goto _again;
f28:
#line 219 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notstored; }
	goto _again;
f11:
#line 220 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_exists; }
	goto _again;
f27:
#line 221 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
	goto _again;
f9:
#line 222 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_deleted; }
	goto _again;
f44:
#line 275 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->noreply = true;
}
	goto _again;
f26:
#line 309 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->number = -1;}
	goto _again;
f19:
#line 310 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* the binary data of a specified isn't really regular, so we drop out of
     the state machine and read it, then come back in to finish the
     "\r\nEND\r\n". */
  parser->parser_state = parser_body;
  {p++; goto _out; }
}
	goto _again;
f36:
#line 320 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_found; }
	goto _again;
f3:
#line 325 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
	goto _again;
f18:
#line 329 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
	goto _again;
f22:
#line 331 "mcrouter/lib/mc/ascii_client.rl"
	{parser->msg->result = mc_res_found;}
	goto _again;
f2:
#line 335 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
	goto _again;
f32:
#line 388 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_ok; }
	goto _again;
f29:
#line 390 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_ok; }
	goto _again;
f76:
#line 417 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_set; }
	goto _again;
f41:
#line 418 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_add; }
	goto _again;
f75:
#line 419 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_replace; }
	goto _again;
f71:
#line 420 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_lease_set; }
	goto _again;
f48:
#line 421 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_append; }
	goto _again;
f73:
#line 422 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_prepend; }
	goto _again;
f56:
#line 426 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_delete; }
	goto _again;
f62:
#line 428 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_get; }
	goto _again;
f63:
#line 429 "mcrouter/lib/mc/ascii_client.rl"
	{parser->msg->op = mc_op_gets; }
	goto _again;
f70:
#line 430 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_lease_get; }
	goto _again;
f72:
#line 431 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_metaget; }
	goto _again;
f69:
#line 433 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_incr; }
	goto _again;
f52:
#line 434 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_decr; }
	goto _again;
f79:
#line 436 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_version; }
	goto _again;
f74:
#line 438 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_quit;
                     parser->msg->noreply = true; }
	goto _again;
f78:
#line 441 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_stats; }
	goto _again;
f45:
#line 443 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_exec; }
	goto _again;
f77:
#line 445 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_shutdown; }
	goto _again;
f59:
#line 447 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_flushall; }
	goto _again;
f61:
#line 448 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->op = mc_op_flushre; }
	goto _again;
f49:
#line 450 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->op = mc_op_cas;
}
	goto _again;
f68:
#line 458 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->op = mc_op_end;
}
	goto _again;
f13:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 75 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    if (tlen > MC_KEY_MAX_LEN_ASCII) {
      parser->bad_key = 1;
    }
    if (parser->bad_key) {
      parser->msg->result = mc_res_bad_key;
    } else {
      if (mc_msg_grow(&parser->msg, tlen + 1,
                      (void**) &parser->msg->key.str) != 0) {
        parser->error = parser_out_of_memory;
        {cs = 745; goto _again;}
      }
      parser->msg->key.len = tlen;
      strncpy(parser->msg->key.str, ts, tlen);
      FBI_ASSERT(!memcmp(parser->msg->key.str, ts, tlen));
      parser->msg->key.str[tlen] = '\0';
    }
  }
  parser->in_skipped_key = 0;
  parser->in_key = 0;
  parser->bad_key = 0;
}
	goto _again;
f5:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 227 "mcrouter/lib/mc/ascii_client.rl"
	{
    parser->msg->delta = strtoll(ts, NULL, 10);
    parser->msg->result = mc_res_stored;
  }
	goto _again;
f47:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 244 "mcrouter/lib/mc/ascii_client.rl"
	{
  while (tlen > 0 && isspace(ts[tlen-1])) {
    tlen--;
  }
  if (mc_msg_grow(&parser->msg, tlen+1, (void**) &parser->msg->key.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->key.len = tlen;
  strncpy(parser->msg->key.str, ts, tlen);
  parser->msg->key.str[tlen] = '\0';
}
	goto _again;
f14:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 257 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->lease_id = strtol(ts, NULL, 10);
}
	goto _again;
f51:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 260 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->cas = strtoll(ts, NULL, 10);
}
	goto _again;
f15:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 263 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->flags = strtoll(ts, NULL, 10);
}
	goto _again;
f24:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 266 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->exptime = strtol(ts, NULL, 10);
}
	goto _again;
f54:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 269 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->delta = strtoll(ts, NULL, 10);
}
	goto _again;
f23:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 272 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->number = strtoll(ts, NULL, 10);
}
	goto _again;
f17:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 279 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* prepare for receiving data */
  size_t len = parser->resid = strtol(ts, NULL, 10);
  parser->off = 0;

  if (mc_msg_grow(&parser->msg, len + 1,
                  (void**) &parser->msg->value.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->value.str[len] = '\0';
  parser->msg->value.len = len;
}
	goto _again;
f21:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 292 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->cas = strtoull(ts, NULL, 10);
}
	goto _again;
f25:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 298 "mcrouter/lib/mc/ascii_client.rl"
	{
  ts[tlen]='\0';
  parser->msg->ipv = 0;
  if (strchr(ts, ':') == NULL) {
    if (inet_pton(AF_INET, ts, &parser->msg->ip_addr) > 0)
      parser->msg->ipv = 4;
  } else {
    if (inet_pton(AF_INET6, ts, &parser->msg->ip_addr) > 0)
      parser->msg->ipv = 6;
  }
}
	goto _again;
f33:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 346 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->msg->stats == NULL) {
    FBI_ASSERT(parser->msg->number == 0);
    size_t stats_size = sizeof(nstring_t) * 2 * MAX_NUM_STATS;
    if (mc_msg_grow(&parser->msg, stats_size, (void**) &parser->msg->stats)) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    memset(parser->msg->stats, 0, stats_size);
  }

  if (parser->msg->number < MAX_NUM_STATS) {
    parser->msg->number++;

    int idx = (parser->msg->number * 2) - 2;
    if (mc_msg_grow(&parser->msg, tlen + 1,
                    (void**) &parser->msg->stats[idx].str) != 0) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    parser->msg->stats[idx].len = tlen;
    parser->msg->stats[idx].str[tlen] = '\0';
    strncpy(parser->msg->stats[idx].str, ts, tlen);
  }
}
	goto _again;
f34:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 373 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->msg->number <= MAX_NUM_STATS) {
    int idx = (parser->msg->number * 2) - 1;
    if (mc_msg_grow(&parser->msg, tlen + 1,
                    (void**) &parser->msg->stats[idx].str) != 0) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }

    parser->msg->stats[idx].len = tlen;
    parser->msg->stats[idx].str[tlen] = '\0';
    strncpy(parser->msg->stats[idx].str, ts, tlen);
  }
}
	goto _again;
f40:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 392 "mcrouter/lib/mc/ascii_client.rl"
	{
    // use new_msg because msg stays live if realloc fails and can leak
    mc_msg_t *new_msg = mc_msg_realloc(parser->msg,
                                       parser->msg->_extra_size + tlen + 1);
    if (new_msg == NULL) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    parser->msg = new_msg;
    parser->msg->result = mc_res_ok;
    char* version = parser->msg->value.str = (char *) &parser->msg[1];
    parser->msg->value.len = tlen;
    strncpy(version, ts, tlen);
    version[tlen] = '\0';
  }
	goto _again;
f12:
#line 233 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->in_skipped_key = 1; parser->in_key = 1; }
#line 31 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    parser->partial_token = 1;
    parser->te = parser->tbuf;
    ts = p;
  }
}
	goto _again;
f42:
#line 238 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->in_skipped_key = 0; parser->in_key = 1; }
#line 31 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    parser->partial_token = 1;
    parser->te = parser->tbuf;
    ts = p;
  }
}
	goto _again;
f55:
#line 275 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->noreply = true;
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f43:
#line 275 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->noreply = true;
}
#line 310 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* the binary data of a specified isn't really regular, so we drop out of
     the state machine and read it, then come back in to finish the
     "\r\nEND\r\n". */
  parser->parser_state = parser_body;
  {p++; goto _out; }
}
	goto _again;
f1:
#line 325 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
#line 335 "mcrouter/lib/mc/ascii_client.rl"
	{ parser->msg->result = mc_res_notfound; }
	goto _again;
f67:
#line 458 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->op = mc_op_end;
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f38:
#line 31 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    parser->partial_token = 1;
    parser->te = parser->tbuf;
    ts = p;
  }
}
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 392 "mcrouter/lib/mc/ascii_client.rl"
	{
    // use new_msg because msg stays live if realloc fails and can leak
    mc_msg_t *new_msg = mc_msg_realloc(parser->msg,
                                       parser->msg->_extra_size + tlen + 1);
    if (new_msg == NULL) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    parser->msg = new_msg;
    parser->msg->result = mc_res_ok;
    char* version = parser->msg->value.str = (char *) &parser->msg[1];
    parser->msg->value.len = tlen;
    strncpy(version, ts, tlen);
    version[tlen] = '\0';
  }
	goto _again;
f57:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 75 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    if (tlen > MC_KEY_MAX_LEN_ASCII) {
      parser->bad_key = 1;
    }
    if (parser->bad_key) {
      parser->msg->result = mc_res_bad_key;
    } else {
      if (mc_msg_grow(&parser->msg, tlen + 1,
                      (void**) &parser->msg->key.str) != 0) {
        parser->error = parser_out_of_memory;
        {cs = 745; goto _again;}
      }
      parser->msg->key.len = tlen;
      strncpy(parser->msg->key.str, ts, tlen);
      FBI_ASSERT(!memcmp(parser->msg->key.str, ts, tlen));
      parser->msg->key.str[tlen] = '\0';
    }
  }
  parser->in_skipped_key = 0;
  parser->in_key = 0;
  parser->bad_key = 0;
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f66:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 75 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    if (tlen > MC_KEY_MAX_LEN_ASCII) {
      parser->bad_key = 1;
    }
    if (parser->bad_key) {
      parser->msg->result = mc_res_bad_key;
    } else {
      if (mc_msg_grow(&parser->msg, tlen + 1,
                      (void**) &parser->msg->key.str) != 0) {
        parser->error = parser_out_of_memory;
        {cs = 745; goto _again;}
      }
      parser->msg->key.len = tlen;
      strncpy(parser->msg->key.str, ts, tlen);
      FBI_ASSERT(!memcmp(parser->msg->key.str, ts, tlen));
      parser->msg->key.str[tlen] = '\0';
    }
  }
  parser->in_skipped_key = 0;
  parser->in_key = 0;
  parser->bad_key = 0;
}
#line 197 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  mc_op_t op = parser->msg->op;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = mc_msg_new(0);
  parser->msg_ready(parser->context, 0, msg);
  if (parser->msg == NULL) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }

  parser->msg->op = op;
}
	goto _again;
f4:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 227 "mcrouter/lib/mc/ascii_client.rl"
	{
    parser->msg->delta = strtoll(ts, NULL, 10);
    parser->msg->result = mc_res_stored;
  }
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f46:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 244 "mcrouter/lib/mc/ascii_client.rl"
	{
  while (tlen > 0 && isspace(ts[tlen-1])) {
    tlen--;
  }
  if (mc_msg_grow(&parser->msg, tlen+1, (void**) &parser->msg->key.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->key.len = tlen;
  strncpy(parser->msg->key.str, ts, tlen);
  parser->msg->key.str[tlen] = '\0';
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f50:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 260 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->cas = strtoll(ts, NULL, 10);
}
#line 310 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* the binary data of a specified isn't really regular, so we drop out of
     the state machine and read it, then come back in to finish the
     "\r\nEND\r\n". */
  parser->parser_state = parser_body;
  {p++; goto _out; }
}
	goto _again;
f58:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 266 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->exptime = strtol(ts, NULL, 10);
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f53:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 269 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->delta = strtoll(ts, NULL, 10);
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f60:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 272 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->number = strtoll(ts, NULL, 10);
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f16:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 279 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* prepare for receiving data */
  size_t len = parser->resid = strtol(ts, NULL, 10);
  parser->off = 0;

  if (mc_msg_grow(&parser->msg, len + 1,
                  (void**) &parser->msg->value.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->value.str[len] = '\0';
  parser->msg->value.len = len;
}
#line 310 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* the binary data of a specified isn't really regular, so we drop out of
     the state machine and read it, then come back in to finish the
     "\r\nEND\r\n". */
  parser->parser_state = parser_body;
  {p++; goto _out; }
}
	goto _again;
f20:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 292 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->cas = strtoull(ts, NULL, 10);
}
#line 310 "mcrouter/lib/mc/ascii_client.rl"
	{
  /* the binary data of a specified isn't really regular, so we drop out of
     the state machine and read it, then come back in to finish the
     "\r\nEND\r\n". */
  parser->parser_state = parser_body;
  {p++; goto _out; }
}
	goto _again;
f39:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 392 "mcrouter/lib/mc/ascii_client.rl"
	{
    // use new_msg because msg stays live if realloc fails and can leak
    mc_msg_t *new_msg = mc_msg_realloc(parser->msg,
                                       parser->msg->_extra_size + tlen + 1);
    if (new_msg == NULL) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    parser->msg = new_msg;
    parser->msg->result = mc_res_ok;
    char* version = parser->msg->value.str = (char *) &parser->msg[1];
    parser->msg->value.len = tlen;
    strncpy(version, ts, tlen);
    version[tlen] = '\0';
  }
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f37:
#line 31 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    parser->partial_token = 1;
    parser->te = parser->tbuf;
    ts = p;
  }
}
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 392 "mcrouter/lib/mc/ascii_client.rl"
	{
    // use new_msg because msg stays live if realloc fails and can leak
    mc_msg_t *new_msg = mc_msg_realloc(parser->msg,
                                       parser->msg->_extra_size + tlen + 1);
    if (new_msg == NULL) {
      parser->error = parser_out_of_memory;
      {cs = 745; goto _again;}
    }
    parser->msg = new_msg;
    parser->msg->result = mc_res_ok;
    char* version = parser->msg->value.str = (char *) &parser->msg[1];
    parser->msg->value.len = tlen;
    strncpy(version, ts, tlen);
    version[tlen] = '\0';
  }
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f65:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 75 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    if (tlen > MC_KEY_MAX_LEN_ASCII) {
      parser->bad_key = 1;
    }
    if (parser->bad_key) {
      parser->msg->result = mc_res_bad_key;
    } else {
      if (mc_msg_grow(&parser->msg, tlen + 1,
                      (void**) &parser->msg->key.str) != 0) {
        parser->error = parser_out_of_memory;
        {cs = 745; goto _again;}
      }
      parser->msg->key.len = tlen;
      strncpy(parser->msg->key.str, ts, tlen);
      FBI_ASSERT(!memcmp(parser->msg->key.str, ts, tlen));
      parser->msg->key.str[tlen] = '\0';
    }
  }
  parser->in_skipped_key = 0;
  parser->in_key = 0;
  parser->bad_key = 0;
}
#line 197 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  mc_op_t op = parser->msg->op;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = mc_msg_new(0);
  parser->msg_ready(parser->context, 0, msg);
  if (parser->msg == NULL) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }

  parser->msg->op = op;
}
#line 458 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->op = mc_op_end;
}
	goto _again;
f30:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 137 "mcrouter/lib/mc/ascii_client.rl"
	{
  // Since the token we are parsing includes the \r\n, we need
  // to invoke this code upon entering the DFA's final state.
  // Only the '\r' is stored in the token buffer, so we only
  // need to remove one character.
  tlen--;
  if (mc_msg_grow(&parser->msg, tlen + 1,
                  (void**) &parser->msg->value.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->value.len = tlen;
  memcpy(parser->msg->value.str, ts, tlen);
  parser->msg->value.str[tlen] = '\0';
}
#line 166 "mcrouter/lib/mc/ascii_client.rl"
	{
    if (parser->msg->err_code == SERVER_ERROR_BUSY) {
      parser->msg->result = mc_res_busy;
    } else {
      parser->msg->result = mc_res_remote_error;
    }
  }
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f7:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 137 "mcrouter/lib/mc/ascii_client.rl"
	{
  // Since the token we are parsing includes the \r\n, we need
  // to invoke this code upon entering the DFA's final state.
  // Only the '\r' is stored in the token buffer, so we only
  // need to remove one character.
  tlen--;
  if (mc_msg_grow(&parser->msg, tlen + 1,
                  (void**) &parser->msg->value.str) != 0) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }
  parser->msg->value.len = tlen;
  memcpy(parser->msg->value.str, ts, tlen);
  parser->msg->value.str[tlen] = '\0';
}
#line 180 "mcrouter/lib/mc/ascii_client.rl"
	{
    parser->msg->result = mc_res_client_error;
  }
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;
f64:
#line 38 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->partial_token && !skipping_key(parser)) {
    FBI_ASSERT(ts);
    parser->partial_token = 0;
    if (parser->te && parser->te > parser->tbuf) {
      /* we have something stuffed in our cheeks,
         let's put them together and update ts. */
      FBI_ASSERT(ts <= p);
      size_t n = p - ts;
      if(mc_parser_ensure_tbuf(parser, n) != 0) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      } else {
        strncpy(parser->te, ts, n);
        parser->te += n;
        *parser->te = '\0';
        tlen = parser->te - parser->tbuf;
        ts = parser->tbuf;
      }
    } else {
      tlen = p - ts;
      if (tlen >= MC_TOKEN_MAX_LEN) {
        if (parser->in_key) {
          parser->bad_key = 1;
        } else {
          parser->error = parser_malformed_request;
          {cs = 745; goto _again;}
        }
      }
    }
  }
}
#line 75 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (!skipping_key(parser)) {
    if (tlen > MC_KEY_MAX_LEN_ASCII) {
      parser->bad_key = 1;
    }
    if (parser->bad_key) {
      parser->msg->result = mc_res_bad_key;
    } else {
      if (mc_msg_grow(&parser->msg, tlen + 1,
                      (void**) &parser->msg->key.str) != 0) {
        parser->error = parser_out_of_memory;
        {cs = 745; goto _again;}
      }
      parser->msg->key.len = tlen;
      strncpy(parser->msg->key.str, ts, tlen);
      FBI_ASSERT(!memcmp(parser->msg->key.str, ts, tlen));
      parser->msg->key.str[tlen] = '\0';
    }
  }
  parser->in_skipped_key = 0;
  parser->in_key = 0;
  parser->bad_key = 0;
}
#line 197 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  mc_op_t op = parser->msg->op;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = mc_msg_new(0);
  parser->msg_ready(parser->context, 0, msg);
  if (parser->msg == NULL) {
    parser->error = parser_out_of_memory;
    {cs = 745; goto _again;}
  }

  parser->msg->op = op;
}
#line 458 "mcrouter/lib/mc/ascii_client.rl"
	{
  parser->msg->op = mc_op_end;
}
#line 99 "mcrouter/lib/mc/ascii_client.rl"
	{
  FBI_ASSERT(parser->msg != NULL);

  // end of msg, fake eof
  pe = eof = p + 1;
  parser->parser_state = parser_msg_header;
  /* Note: we need to reset parser->msg first,
     in case mc_parser_reset is called from the callback */
  mc_msg_t* msg = parser->msg;
  parser->msg = NULL;
  parser->msg_ready(parser->context, 0, msg);
  nmsgs++;

  mc_parser_cleanup_tbuf(parser);
}
	goto _again;

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	switch ( _ascii_eof_actions[cs] ) {
	case 81:
#line 121 "mcrouter/lib/mc/ascii_client.rl"
	{
  if (parser->msg != NULL) {
    mc_msg_decref(parser->msg);
  }
  parser->msg = NULL;
  parser->te = NULL;
  parser->in_key = 0;
  parser->bad_key = 0;
  {p++; goto _out; }
}
	break;
#line 7370 "ascii_client.c"
	}
	}

	_out: {}
	}

#line 603 "mcrouter/lib/mc/ascii_client.rl"

      // If we encountered 'ERROR' reply, fail all further data.
      if (isError) {
        goto epilogue;
      }

      /* if msg == NULL, we finished the msg */
      if (parser->msg) {
        parser->ragel_state = cs;
      } else {
        /* sentinel values */
        parser->ragel_state = ascii_error;
      }

      if (ts && parser->partial_token) {
        // we're in the middle of a token, stuff it in our cheeks
        int n = p - ts;
        if(mc_parser_ensure_tbuf(parser, n) == 0) {
          strncpy(parser->te, ts, n);
          parser->te += n;
        } else {
          if (parser->in_key) {
            parser->bad_key = 1;
          } else {
            // fake fgoto error here
            parser->error = parser_malformed_request;
            cs = ascii_error;
          }
        }
      }

      if (cs == ascii_error) {
        if (parser->msg != NULL) {
          mc_msg_decref(parser->msg);
          parser->msg = NULL;
        }
        parser->resid = parser->off = 0;
        parser->parse_error(parser->context, parser->error);
        goto epilogue;
      }
    }

    /* We may have adjusted pe and eof to simulate EOF at the end of a msg.
       Restore them for continued parsing of additional msgs. */
    pe = buf + nbuf;
    eof = NULL;
  }

  success = 1;

epilogue:
  dbg_fexit("%d msgs finished. parser_state=%s cs=%d",
            nmsgs, parser_state_to_string(parser->parser_state), cs);
  return success;
}


#line 661 "mcrouter/lib/mc/ascii_client.rl"

