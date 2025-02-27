      subroutine GET_PERM_WEIGHT()
      implicit none
      include 'nexternal.inc'
      include 'coupl.inc'
      include 'permutation.inc'
      integer perm
      integer perm_id(nexternal-2)
      integer content(nexternal)
      integer i
      double precision WEIGHT
      double precision weight_perm_global, weight_perm_BW
      external weight_perm_global, weight_perm_BW


      do perm = 1, NPERM
         curr_perm = perm
         call get_perm(perm, perm_id)
         call assign_perm(perm_id)

        
        weight = weight_perm_global(perm,perm_id)
                  content(1) = 4
          content(2) = 3
          content(3) = 0
                weight = weight * weight_perm_BW(perm, perm_id, mdl_MW, mdl_WW, content, 24)
                
        perm_value(perm, 1) = weight
      enddo
      return
      end
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
cc                                    PERMUTATION MODULE                                   cc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     Need to contain TWO functions:                                                       cc                   
c           - weight_perm_global                                                           cc
c           - weight_perm_BW  (associate to a given propagator                             cc
c    The total wieght is the product of those weight. The permuation below a given         cc
c           relative cutoff are not consider for the integration.                          cc
c    The default function consist in a simple breit-wigner with an effective width dependingc
c            on the width of the transfer functions.                                        c
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

      double precision function weight_perm_global(perm, perm_id)
      implicit none
      include 'nexternal.inc'
      integer perm ! perm unique identifier
      integer perm_id(nexternal-2) !order of the particles.
      !      
      !  DO nothing
      !
      weight_perm_global = 1d0
      !
      !  FORCE ONE OF THE B to tagged. b have position 3 and 6 in MG (p p > t t~, (t > w+ b, w+ > l+ vl), (t~ > w- b~, w- > j j)
      !
      return 
      end
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c     ANOTHER OPTION:
c     FORCE ONE OF THE B to tagged. b have position 3 and 6 in MG (p p > t t~, (t > w+ b, w+ > l+ vl), (t~ > w- b~, w- > j j)
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c       double precision function weight_perm_global(perm, perm_id)
c       implicit none
c       include 'nexternal.inc'       
c       integer perm ! perm unique identifier
c       integer perm_id(nexternal-2) !order of the particles.
c       integer tag_lhco(3:nexternal)
c       common/lhco_order/tag_lhco   ! get the id of the line of the LHCO information
c
c LHCO input
c
c	inclucde 'maxparticles.inc'
c        integer tag_init(3:max_particles),type(max_particles),run_number,trigger
c        double precision eta_init(max_particles),phi_init(max_particles),
c     &pt_init(max_particles),j_mass(max_particles),ntrk(max_particles),
c     &btag(max_particles),had_em(max_particles),dummy1(max_particles),
c     &dummy2(max_particles)
c         common/LHCO_input/eta_init,phi_init,pt_init,
c     &j_mass,ntrk,btag,had_em,dummy1,dummy2,tag_init,type,run_number,
c     &trigger
c      integer lhco_b1, lhco_b2  
c
c      lhco_b1 = tag_lhco(3)   
c      lhco_b2 = tag_lhco(6)
c       if (btag(lhco_b1).eq.0d0.and.btag(lhco_b2).eq.0d0) then
c          weight_perm_global = 0d0
c       else
c          weight_perm_global = 1d0
c       endif
c       end
c       return
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      double precision function weight_perm_BW(perm, perm_id, Mass, Width, content, id)
      implicit none
      include 'nexternal.inc'
      include 'maxparticles.inc'
      include 'permutation.inc'
      integer perm_id(nexternal-2)
      integer perm
      integer content(nexternal)
      integer id
      double precision Mass, Width, InvMass2
      integer i,j,k
      double precision E_error(3:nexternal), eta_error(3:nexternal), phi_error(3:nexternal)
      double precision p_temp(0:3)
      double precision dot
      external dot
      double precision pexp(0:3,nexternal)
      integer tag_lhco(3:nexternal)
      common/to_pexp/pexp
      common/lhco_order/tag_lhco
      double precision c_point(NPERM,1:max_particles,3,2)
      common/ph_sp_init/c_point
c
c     User define parameter
c      
      double precision pi
      data pi/3.14159265359d0/ 
      double precision eff_width
c
c     Generic function
c
      do i=3, nexternal
         E_error(i) = c_point(perm,i,1,2)
         eta_error(i) =c_point(perm,i,2,2)
         phi_error(i) = c_point(perm,i,3,2)
      enddo
      do i=0,3
         p_temp(i) = 0d0
      enddo
      do i =1, nexternal
         j = content(i)
         if (j.gt.0) then
            p_temp(0) = p_temp(0) + pexp(0,j)
            p_temp(1) = p_temp(1) + pexp(1,j)
            p_temp(2) = p_temp(2) + pexp(2,j)
            p_temp(3) = p_temp(3) + pexp(3,j)
         else
            EXIT
         endif
      enddo
      InvMass2 = DOT(p_temp, p_temp) 
c
c     weighting by the Breit-Wigner
c
      eff_width = width**2
      do i = 1, nexternal
         if (content(i).gt.0) then
            if (E_error(content(i)).eq.-1d0)then
               weight_perm_bw = 1d0 ! no weight since neutrino!
               return
            endif
            eff_width = eff_width + E_error(content(i))**2
         else
            EXIT
         endif
      enddo
      eff_width = DSQRT(eff_width)
      weight_perm_bw = (InvMass2-Mass**2)**2+Mass**2*Width**2
      weight_perm_bw = Mass*Width/weight_perm_bw/pi
      return
      end
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
