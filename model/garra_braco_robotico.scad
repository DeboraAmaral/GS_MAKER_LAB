/* ============================================================

    BRAÇO ROBÓTICO INDUSTRIAL — Docking & Retrieval

    Debora da Silva Amaral - RM550412 
    
    Eduardo Pielich Sanchez - RM99767
    
    Gabriel Machado Carrara Pimentel - RM99880
    
    Livia Namba Seraphim - RM97819 
    
    Vitor Hugo Gonçalves Rodrigues - RM97758
    ============================================================ */

$fn = 60;

base_r         = 38;   
base_h         = 14;   
pedestal_r     = 28;  
pedestal_h     = 30;   

ombro_r        = 22;   
ombro_larg     = 50;   

braco_comp     = 90;   
braco_larg     = 18;   
braco_esp      = 14;  

cotovelo_r     = 16;   

ante_comp      = 70;   
ante_r         = 10;   

punho_r        = 12;   

garra_base_r   = 11;   
garra_base_h   = 14; 

dedo_comp      = 28;   
dedo_larg      = 6;    
dedo_esp       = 5;    
n_dedos        = 3;    
abertura_ang   = 18;   

/* ── MÓDULOS ────────────────────────────────────────────────*/

module base_giratoria() {
    cylinder(h=base_h, r1=base_r, r2=base_r*0.85);
    for (a=[0,90,180,270])
        rotate([0,0,a])
            translate([base_r*0.7, 0, base_h*0.5])
                cylinder(h=base_h*0.6, r=3, center=true);
    translate([0,0,base_h])
        cylinder(h=pedestal_h, r1=pedestal_r, r2=pedestal_r*0.9);
    translate([0,0,base_h+pedestal_h-4])
        difference(){
            cylinder(h=6, r=pedestal_r*0.95);
            cylinder(h=8, r=pedestal_r*0.7);
        }
}

module joint(r, larg, cor="Silver") {
    color(cor)
    rotate([90,0,0])
        translate([0,0,-larg/2])
            difference(){
                cylinder(h=larg, r=r);
                for(s=[-1,1])
                    translate([0,0, larg/2 + s*(larg/2-4)])
                        difference(){
                            cylinder(h=4, r=r+0.1, center=true);
                            cylinder(h=6, r=r-3, center=true);
                        }
            }
}

module link_braco(comp, larg, esp) {
    hull(){
        translate([0, -larg/2, -esp/2])
            rotate([-90,0,0]) cylinder(h=larg, r=esp/2);
        translate([comp, -larg/2, -esp/2])
            rotate([-90,0,0]) cylinder(h=larg, r=esp/2*0.8);
    }
    translate([comp*0.1, -1.5, -esp*0.35])
        cube([comp*0.8, 3, esp*0.7]);
}

module antebraco(comp, r) {
    cylinder(h=comp, r1=r, r2=r*0.85);
    cylinder(h=5, r=r*1.4);
    translate([0,0,comp-4])
        cylinder(h=5, r=r*1.2);
}

module garra() {
    difference(){
        cylinder(h=garra_base_h, r=garra_base_r);
        translate([0,0,-1])
            cylinder(h=garra_base_h+2, r=garra_base_r*0.45);
        for(a=[0:360/n_dedos:359])
            rotate([0,0,a])
                translate([0,-dedo_larg/2,-1])
                    cube([garra_base_r+2, dedo_larg, garra_base_h+2]);
    }

    for(a=[0:360/n_dedos:359]) {
        rotate([0,0,a])
        translate([garra_base_r*0.6, 0, garra_base_h]) {
            rotate([-abertura_ang,0,0])
                union(){
                    cube([dedo_esp, dedo_larg, dedo_comp*0.55], center=false);
                    translate([0,0,dedo_comp*0.5])
                    rotate([abertura_ang*2.2,0,0])
                        cube([dedo_esp, dedo_larg*0.8, dedo_comp*0.45]);
                }
        }
    }
}

module punho(r) {
    difference(){
        sphere(r=r);
        translate([0,0,-r*1.1]) cube([r*3,r*3,r*1.1], center=true);
        translate([0,0, r*0.6]) cube([r*3,r*3,r*1.1], center=true);
    }
}

/* ── MONTAGEM COMPLETA ──────────────────────────────────────*/

color("#CC5500")
    base_giratoria();

translate([0, 0, base_h + pedestal_h + 4]) {
    color("#DD6600")
        joint(ombro_r, ombro_larg);
    
    translate([0, 0, 0])
    rotate([65, 0, 0])
    translate([0, 0, ombro_r]) {
        color("#CC5500")
            link_braco(braco_comp, braco_larg, braco_esp);

        translate([braco_comp, 0, 0]) {
            color("#DD6600")
                joint(cotovelo_r, braco_larg*0.9);

            rotate([-50, 0, 0])
            translate([0, 0, cotovelo_r]) {
                color("#CC5500")
                    antebraco(ante_comp, ante_r);

                translate([0, 0, ante_comp + 2]) {
                    color("#555555")
                        punho(punho_r);
                    translate([0,0, punho_r*0.6])
                    color("#444444")
                    difference(){
                        cylinder(h=8, r=punho_r*0.9, center=true);
                        cylinder(h=10, r=punho_r*0.5, center=true);
                    }

                    translate([0, 0, punho_r + 4])
                    color("#333333")
                        garra();
                }
            }
        }
    }
}
