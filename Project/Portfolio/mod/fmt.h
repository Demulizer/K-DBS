#ifndef FMT_H
#define FMT_H

/* --- [ NAMESPACING ] ---
 * Example usage:
 *  Feed    - K_(xyz)
 *  Token   - KDBS_xyz
 */
#define K_(_) KDBS_##_
/* - - - */

/* --- [ ASSETS ] --- */
// Custom boolean
#define KDBS_TRU 1
#define KDBS_FLS 0
/* - - - */

/* --- [ ERROR ] --- */

/* Error data
 * HeaDeR
 * MeSsaGe
 * FaTaL?-(T/F)
*/
typedef struct {
    const char* hdr;
    const char* msg;
    int         ftl;
} K_(ERR_DAT);

// Error message list
#define KDBS_ERR_RMU_MSG "./KDBS \"config\""

/* Master error list
 * X(ERROR_HEADER, REFERENCE, FATALITY)
*/
#define KDBS_ERR_LST \
    X("RECOMMENDED USAGE", RMU, KDBS_FLS)

// Assign error ids
#define X(_, e, f) KDBS_ERR_##e,
enum {
    KDBS_ERR_LST
    KDBS_ERR_CNT
};
#undef X

/* Error collection
 * errorlist[REFERENCE_INDEX] = { HEADER, MESSAGE };
*/
#define X(_, e, f) [KDBS_ERR_##e] = { _, KDBS_ERR_##e##_MSG, f},
static const K_(ERR_DAT) errorList[KDBS_ERR_CNT] = {
    KDBS_ERR_LST
};
#undef X

/* Error message format-er
 * Feed     - K_(ERROR(REFERENCE_INDEX))
 * Output   - \n\t:: ERROR_HEADER ::\n
 *            \n-|  ERROR_MESSAGE\n\n
 *            ---[ REFERENCE_INDEX ]---\n\n
*/
#define KDBS_ERROR(_) do {                  \
    fprintf(stderr,                         \
        "\n:: %s ::"                        \
        "\n-| %s"                           \
        "\n---[ %d.%s ]---\n\n",            \
        errorList[_].hdr,                   \
        errorList[_].msg,                   \
        _, errorList[_].ftl ?               \
        "error" : "expect"                  \
    );                                      \
} while(0)
/* - - - */

#endif