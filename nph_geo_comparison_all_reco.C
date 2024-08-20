#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TCanvas.h"
#include "TROOT.h"

/// @brief
void nph_geo_comparison_all_reco()
{
    TFile *file_standalone[25];
    TTree *tree_standalone[25];

    TString path_standalone_6_4("/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_0.01KHz_32_pixel_reco/output_files/");
    TString path_standalone_5_4("/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_10KHz_32_pixel_reco/output_files/");
    TString path_standalone_mcp("/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_mcp_reco/output_files/");
    TString path_standalone_100KHz("/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_100KHz_32_pixel_reco/output_files/");
    TString path_standalone_1KHz("/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_1KHz_32_pixel_reco/output_files/");

    TString in_standalone_6_4[25];
    TString in_standalone_5_4[25];
    TString in_standalone_mcp[25];
    TString in_standalone_100KHz[25];
    TString in_standalone_1KHz[25];

    Int_t theta_value[25];
    Double_t theta[25];
    Double_t theta_err[25] = {0};

    for (int i = 0; i < 25; i++)
    {
        theta_value[i] = 30 + 5 * i;
        theta[i] = 30 + 5 * i;
    }

    Double_t nph_ti_standalone_6_4[25];
    Double_t nph_ti_err_standalone_6_4[25];
    Double_t nph_ti[5], nph_ti_err[5];

    Double_t nph_ti_standalone_5_4[25];
    Double_t nph_ti_err_standalone_5_4[25];

    Double_t nph_ti_standalone_mcp[25];
    Double_t nph_ti_err_standalone_mcp[25];

    Double_t nph_ti_standalone_100KHz[25];
    Double_t nph_ti_err_standalone_100KHz[25];

    Double_t nph_ti_standalone_1KHz[25];
    Double_t nph_ti_err_standalone_1KHz[25];

    for (int j = 0; j < 25; j++)
    {
        in_standalone_6_4[j] = Form(path_standalone_6_4 + "output_%1.0d_deg.root", theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_6_4[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("nph_ti", &nph_ti);
        tree_standalone[j]->SetBranchAddress("nph_ti_err", &nph_ti_err);
        tree_standalone[j]->GetEntry(0);

        nph_ti_standalone_6_4[j] = nph_ti[2];
        nph_ti_err_standalone_6_4[j] = nph_ti_err[2];

        file_standalone[j]->Close();

        in_standalone_5_4[j] = Form(path_standalone_5_4 + "output_%1.0d_deg.root", theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_5_4[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("nph_ti", &nph_ti);
        tree_standalone[j]->SetBranchAddress("nph_ti_err", &nph_ti_err);
        tree_standalone[j]->GetEntry(0);

        nph_ti_standalone_5_4[j] = nph_ti[2];
        nph_ti_err_standalone_5_4[j] = nph_ti_err[2];

        file_standalone[j]->Close();

        in_standalone_mcp[j] = Form(path_standalone_mcp + "output_%1.0d_deg.root", theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_mcp[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("nph_ti", &nph_ti);
        tree_standalone[j]->SetBranchAddress("nph_ti_err", &nph_ti_err);
        tree_standalone[j]->GetEntry(0);

        nph_ti_standalone_mcp[j] = nph_ti[2];
        nph_ti_err_standalone_mcp[j] = nph_ti_err[2];

        file_standalone[j]->Close();

        in_standalone_100KHz[j] = Form(path_standalone_100KHz + "output_%1.0d_deg.root", theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_100KHz[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("nph_ti", &nph_ti);
        tree_standalone[j]->SetBranchAddress("nph_ti_err", &nph_ti_err);
        tree_standalone[j]->GetEntry(0);

        nph_ti_standalone_100KHz[j] = nph_ti[2];
        nph_ti_err_standalone_100KHz[j] = nph_ti_err[2];

        file_standalone[j]->Close();

        in_standalone_1KHz[j] = Form(path_standalone_1KHz + "output_%1.0d_deg.root", theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_1KHz[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("nph_ti", &nph_ti);
        tree_standalone[j]->SetBranchAddress("nph_ti_err", &nph_ti_err);
        tree_standalone[j]->GetEntry(0);

        nph_ti_standalone_1KHz[j] = nph_ti[2];
        nph_ti_err_standalone_1KHz[j] = nph_ti_err[2];

        file_standalone[j]->Close();
    }

    if (gROOT->FindObject("c1"))
        delete gROOT->FindObject("c1");
    TCanvas *c1 = new TCanvas("c1", "Photon Yield", 800, 600);

    TGraphErrors *gr1 = new TGraphErrors(25, theta, nph_ti_standalone_6_4, theta_err, nph_ti_err_standalone_6_4);
    TGraphErrors *gr2 = new TGraphErrors(25, theta, nph_ti_standalone_5_4, theta_err, nph_ti_err_standalone_5_4);
    TGraphErrors *gr3 = new TGraphErrors(25, theta, nph_ti_standalone_mcp, theta_err, nph_ti_err_standalone_mcp);
    TGraphErrors *gr4 = new TGraphErrors(25, theta, nph_ti_standalone_100KHz, theta_err, nph_ti_err_standalone_100KHz);
    TGraphErrors *gr5 = new TGraphErrors(25, theta, nph_ti_standalone_1KHz, theta_err, nph_ti_err_standalone_1KHz);

    gr1->SetTitle("Photon yield at 6 GeV/c - time imaging reco for HRPPD vs 1kHz vs 10KHz vs 100KHz vs standard mcp_pmt");
    gr1->GetXaxis()->SetTitle("Polar angle (deg)");
    gr1->GetYaxis()->SetTitle("Photon yield");
    gr1->GetYaxis()->SetRangeUser(0, 900);
    gr1->GetXaxis()->SetRangeUser(20, 160);
    gr1->GetXaxis()->SetTitleSize(0.05);
    gr1->GetYaxis()->SetTitleSize(0.05);
    gr1->GetXaxis()->SetTitleOffset(0.8);
    gr1->GetYaxis()->SetTitleOffset(0.8);

    gr1->SetMarkerStyle(kFullCircle);
    gr1->SetMarkerSize(1.4);
    gr1->SetMarkerColor(1);
    gr1->SetLineColor(1);
    gr1->Draw("APL");

    gr2->SetMarkerStyle(kFullCircle);
    gr2->SetMarkerSize(1);
    gr2->SetMarkerColor(2);
    gr2->SetLineColor(2);
    gr2->Draw("same");

    gr2->GetYaxis()->SetRangeUser(0, 900);
    gr2->GetXaxis()->SetRangeUser(20, 160);
    gr2->GetXaxis()->SetTitleSize(0.05);
    gr2->GetYaxis()->SetTitleSize(0.05);
    gr2->GetXaxis()->SetTitleOffset(0.8);
    gr2->GetYaxis()->SetTitleOffset(0.8);

    gr3->SetMarkerStyle(kFullCircle);
    gr3->SetMarkerSize(1);
    gr3->SetMarkerColor(3);
    gr3->SetLineColor(3);
    gr3->Draw("same");

    gr4->SetMarkerStyle(kFullCircle);
    gr4->SetMarkerSize(1);
    gr4->SetMarkerColor(4);
    gr4->SetLineColor(4);
    gr4->Draw("same");

    gr5->SetMarkerStyle(kFullCircle);
    gr5->SetMarkerSize(1);
    gr5->SetMarkerColor(6);
    gr5->SetLineColor(6);
    gr5->Draw("same");

    gPad->SetGrid();
}
