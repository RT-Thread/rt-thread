
if [info exists AT91C_MAINOSC_FREQ] {
    # user set this... let it be.
} {
    # 18.432mhz is a common thing...
    set AT91C_MAINOSC_FREQ 18432000
}
global AT91C_MAINOSC_FREQ

if [info exists AT91C_SLOWOSC_FREQ] {
    # user set this... let it be.
} {
    # 32khz is the norm
    set AT91C_SLOWOSC_FREQ 32768
}
global AT91C_SLOWOSC_FREQ
