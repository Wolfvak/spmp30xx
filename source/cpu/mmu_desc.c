#include <spmp/common.h>
#include <spmp/asminc.h>
#include <spmp/cpu/mmu.h>

u32 __build_mmudesc_sect(u32 base, u32 ap, u32 dom, u32 cb) {
    return (base & 0xFFF00000) | \
           ((ap & 0x3) << 10) | ((dom & 0xF) << 5) | \
           (1 << 4) | ((cb & 0x3) << 2) | MMU_SECTION;
}

u32 __build_mmudesc_coarse(u32 *ptbase, u32 dom) {
    return ((u32)ptbase & 0xFFFFFC00) | \
           ((dom & 0xF) << 5) | (1 << 4) | MMU_COARSE;
}

u32 __build_mmudesc_fine(u32 *ptbase, u32 dom) {
    return ((u32)ptbase & 0xFFFFF000) | \
           ((dom & 0xF) << 5) | (1 << 4) | MMU_FINEPAGE;
}

u32 __build_mmupage_large(u32 base, u32 ap, u32 cb) {
    ap &= 0xF;
    return (base & 0xFFFF0000) | \
           (ap << 10) | (ap << 8) | (ap << 6) | (ap << 4) | \
           ((cb & 0x3) << 2) | MMU_LARGEPAGE;
}

u32 __build_mmupage_small(u32 base, u32 ap, u32 cb) {
    ap &= 0xF;
    return (base & 0xFFFFF000) | \
           (ap << 10) | (ap << 8) | (ap << 6) | (ap << 4) | \
           ((cb & 0x3) << 2) | MMU_SMALLPAGE;
}

u32 __build_mmupage_tiny(u32 base, u32 ap, u32 cb) {
    ap &= 0xF;
    return (base & 0xFFFFC000) | \
           ((ap & 0x3) << 4) | \
           ((cb & 0x3) << 2) | MMU_SMALLPAGE;
}
