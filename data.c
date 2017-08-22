/* GRkbd 1.4 - Greek keyboard for the X Window System
 * Copyright (C) 1998-2007 Giannis Tsakiris
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  0XK_Greek_SIGMA1-1307, USA.
 *
 * You can contact the author by e-mail at: giannis.tsakiris@gmail.com
 */

#include <X11/Xlib.h>
#include <X11/keysym.h>

KeySym GREEK[4][30][3] = {
  38, XK_Greek_alpha, XK_Greek_ALPHA,
  56, XK_Greek_beta, XK_Greek_BETA,
  42, XK_Greek_gamma, XK_Greek_GAMMA,
  40, XK_Greek_delta, XK_Greek_DELTA,
  26, XK_Greek_epsilon, XK_Greek_EPSILON,
  52, XK_Greek_zeta, XK_Greek_ZETA,
  43, XK_Greek_eta, XK_Greek_ETA,
  30, XK_Greek_theta, XK_Greek_THETA,
  31, XK_Greek_iota, XK_Greek_IOTA,
  45, XK_Greek_kappa, XK_Greek_KAPPA,
  46, XK_Greek_lamda, XK_Greek_LAMDA,
  58, XK_Greek_mu, XK_Greek_MU,
  57, XK_Greek_nu, XK_Greek_NU,
  44, XK_Greek_xi, XK_Greek_XI,
  32, XK_Greek_omicron, XK_Greek_OMICRON,
  33, XK_Greek_pi, XK_Greek_PI,
  27, XK_Greek_rho, XK_Greek_RHO,
  25, XK_Greek_finalsmallsigma, XK_Greek_SIGMA,
  39, XK_Greek_sigma, XK_Greek_SIGMA,
  28, XK_Greek_tau, XK_Greek_TAU,
  29, XK_Greek_upsilon, XK_Greek_UPSILON,
  41, XK_Greek_phi, XK_Greek_PHI,
  53, XK_Greek_chi, XK_Greek_CHI,
  54, XK_Greek_psi, XK_Greek_PSI,
  55, XK_Greek_omega, XK_Greek_OMEGA,
  24, XK_semicolon, XK_colon,
  48, XK_apostrophe, XK_quotedbl,
  49, XK_grave, XK_asciitilde,
  47, 0, 0,
  67, 0, 0,

  38, XK_Greek_alphaaccent, XK_Greek_ALPHAaccent,
  56, XK_Greek_beta, XK_Greek_BETA,
  42, XK_Greek_gamma, XK_Greek_GAMMA,
  40, XK_Greek_delta, XK_Greek_DELTA,
  26, XK_Greek_epsilonaccent, XK_Greek_EPSILONaccent,
  52, XK_Greek_zeta, XK_Greek_ZETA,
  43, XK_Greek_etaaccent, XK_Greek_ETAaccent,
  30, XK_Greek_theta, XK_Greek_THETA,
  31, XK_Greek_iotaaccent, XK_Greek_IOTAaccent,
  45, XK_Greek_kappa, XK_Greek_KAPPA,
  46, XK_Greek_lamda, XK_Greek_LAMDA,
  58, XK_Greek_mu, XK_Greek_MU,
  57, XK_Greek_nu, XK_Greek_NU,
  44, XK_Greek_xi, XK_Greek_XI,
  32, XK_Greek_omicronaccent, XK_Greek_OMICRONaccent,
  33, XK_Greek_pi, XK_Greek_PI,
  27, XK_Greek_rho, XK_Greek_RHO,
  25, XK_Greek_finalsmallsigma, XK_Greek_SIGMA,
  39, XK_Greek_sigma, XK_Greek_SIGMA,
  28, XK_Greek_tau, XK_Greek_TAU,
  29, XK_Greek_upsilonaccent, XK_Greek_UPSILONaccent,
  41, XK_Greek_phi, XK_Greek_PHI,
  53, XK_Greek_chi, XK_Greek_CHI,
  54, XK_Greek_psi, XK_Greek_PSI,
  55, XK_Greek_omegaaccent, XK_Greek_OMEGAaccent,
  24, XK_semicolon, XK_colon,
  48, XK_apostrophe, XK_quotedbl,
  49, XK_grave, XK_asciitilde,
  47, 0, 0,
  67, 0, 0,

  38, XK_Greek_alpha, XK_Greek_ALPHA,
  56, XK_Greek_beta, XK_Greek_BETA,
  42, XK_Greek_gamma, XK_Greek_GAMMA,
  40, XK_Greek_delta, XK_Greek_DELTA,
  26, XK_Greek_delta, XK_Greek_EPSILON,
  52, XK_Greek_zeta, XK_Greek_ZETA,
  43, XK_Greek_ZETA, XK_Greek_ETA,
  30, XK_Greek_theta, XK_Greek_THETA,
  31, XK_Greek_iotadieresis, XK_Greek_IOTAdiaeresis,
  45, XK_Greek_kappa, XK_Greek_KAPPA,
  46, XK_Greek_lamda, XK_Greek_LAMDA,
  58, XK_Greek_mu, XK_Greek_MU,
  57, XK_Greek_nu, XK_Greek_NU,
  44, XK_Greek_xi, XK_Greek_XI,
  32, XK_Greek_omicron, XK_Greek_OMICRON,
  33, XK_Greek_pi, XK_Greek_PI,
  27, XK_Greek_rho, XK_Greek_RHO,
  25, XK_Greek_finalsmallsigma, XK_Greek_SIGMA,
  39, XK_Greek_sigma, XK_Greek_SIGMA,
  28, XK_Greek_tau, XK_Greek_TAU,
  29, XK_Greek_upsilondieresis, XK_Greek_UPSILONdieresis,
  41, XK_Greek_phi, XK_Greek_PHI,
  53, XK_Greek_chi, XK_Greek_CHI,
  54, XK_Greek_psi, XK_Greek_PSI,
  55, XK_Greek_omega, XK_Greek_OMEGA,
  24, XK_semicolon, XK_colon,
  48, XK_apostrophe, XK_quotedbl,
  49, XK_grave, XK_asciitilde,
  47, 0, 0,
  67, 0, 0,

  38, XK_Greek_alpha, XK_Greek_ALPHA,
  56, XK_Greek_beta, XK_Greek_BETA,
  42, XK_Greek_gamma, XK_Greek_GAMMA,
  40, XK_Greek_delta, XK_Greek_DELTA,
  26, XK_Greek_delta, XK_Greek_EPSILON,
  52, XK_Greek_zeta, XK_Greek_ZETA,
  43, XK_Greek_ZETA, XK_Greek_ETA,
  30, XK_Greek_theta, XK_Greek_THETA,
  31, XK_Greek_iotaaccentdieresis, XK_Greek_IOTAdiaeresis,
  45, XK_Greek_kappa, XK_Greek_KAPPA,
  46, XK_Greek_lamda, XK_Greek_LAMDA,
  58, XK_Greek_mu, XK_Greek_MU,
  57, XK_Greek_nu, XK_Greek_NU,
  44, XK_Greek_xi, XK_Greek_XI,
  32, XK_Greek_omicron, XK_Greek_OMICRON,
  33, XK_Greek_pi, XK_Greek_PI,
  27, XK_Greek_rho, XK_Greek_RHO,
  25, XK_Greek_finalsmallsigma, XK_Greek_SIGMA,
  39, XK_Greek_sigma, XK_Greek_SIGMA,
  28, XK_Greek_tau, XK_Greek_TAU,
  29, XK_Greek_upsilonaccentdieresis, XK_Greek_UPSILONdieresis,
  41, XK_Greek_phi, XK_Greek_PHI,
  53, XK_Greek_chi, XK_Greek_CHI,
  54, XK_Greek_psi, XK_Greek_PSI,
  55, XK_Greek_omega, XK_Greek_OMEGA,
  24, XK_semicolon, XK_colon,
  48, XK_apostrophe, XK_quotedbl,
  49, XK_grave, XK_asciitilde,
  47, 0, 0,
  67, 0, 0
};

void
set_quotes (int state)
{
  int i;
  for (i = 0; i < 4; i++)
    GREEK[i][26][2] = state ? XK_guillemotright : XK_guillemotleft;
}

int deadkeys[9][7] = {
  0, 62, 113, 1, 0, 0, 1,
  1, 62, 113, 0, 0, 0, 1,
  0, 50, 64, 1, 0, 0, 1,
  1, 50, 64, 0, 0, 0, 1,
  1, 47, 50, 1, 1, 2, 0,
  1, 47, 62, 1, 1, 2, 0,
  1, 47, 0, 1, 2, 1, 0,
  0, 113, 0, 1, 0, 0, 1,
  1, 113, 0, 0, 0, 0, 1
};
