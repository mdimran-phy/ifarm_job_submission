#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TString.h>

void spr_geo_edited_comparison_all_reco()
{
    TFile *file_standalone[25];
    TTree *tree_standalone[25];

    TString path_standalone("/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_0.01KHz_reco_tc_0.2ns/output_files/");
    TString path_standalone_5_4("/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_10KHz_reco_tc_0.2ns/output_files/");
    TString path_standalone_mcp("/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_mcp_new_reco_tc_0.2ns/output_files/");
    //TString path_standalone_mcp("/w/halld-scshelf2101/halld3/home/ihossain/gr_standard_6_4_reco/output_files/");
    TString path_standalone_100KHz("/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_100KHz_reco_tc_0.2ns/output_files/");
    TString path_standalone_1KHz("/w/halld-scshelf2101/halld3/home/ihossain/gr_dn_HRPPD_3.3_pixel_1KHz_reco_tc_0.2ns/output_files/");


    TString in_standalone[25];
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

    Double_t spr_gr_standalone[25];
    Double_t spr_gr_err_standalone[25];
    Double_t spr[5], spr_err[5];

    Double_t spr_gr_standalone_5_4[25];
    Double_t spr_gr_err_standalone_5_4[25];

    Double_t spr_gr_standalone_mcp[25];
    Double_t spr_gr_err_standalone_mcp[25];

    Double_t spr_gr_standalone_100KHz[25];
    Double_t spr_gr_err_standalone_100KHz[25];

    Double_t spr_gr_standalone_1KHz[25];
    Double_t spr_gr_err_standalone_1KHz[25];



    for (int j = 0; j < 25; j++)
    {
        in_standalone[j] = Form((path_standalone + "output_%1.0d_deg.root").Data(), theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("spr", &spr);
        tree_standalone[j]->GetEntry(0);
        spr_gr_standalone[j] = spr[2];
        spr_gr_err_standalone[j] = 0.;

        in_standalone_5_4[j] = Form((path_standalone_5_4 + "output_%1.0d_deg.root").Data(), theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_5_4[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("spr", &spr);
        tree_standalone[j]->GetEntry(0);
        spr_gr_standalone_5_4[j] = spr[2];
        spr_gr_err_standalone_5_4[j] = 0.;

        in_standalone_mcp[j] = Form((path_standalone_mcp + "output_%1.0d_deg.root").Data(), theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_mcp[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("spr", &spr);
        tree_standalone[j]->GetEntry(0);
        spr_gr_standalone_mcp[j] = spr[2];
        spr_gr_err_standalone_mcp[j] = 0.;

        in_standalone_100KHz[j] = Form((path_standalone_100KHz + "output_%1.0d_deg.root").Data(), theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_100KHz[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("spr", &spr);
        tree_standalone[j]->GetEntry(0);
        spr_gr_standalone_100KHz[j] = spr[2];
        spr_gr_err_standalone_100KHz[j] = 0.;

        in_standalone_1KHz[j] = Form((path_standalone_1KHz + "output_%1.0d_deg.root").Data(), theta_value[j]);
        file_standalone[j] = TFile::Open(in_standalone_1KHz[j]);
        tree_standalone[j] = (TTree *)file_standalone[j]->Get("reco");

        tree_standalone[j]->SetBranchAddress("spr", &spr);
        tree_standalone[j]->GetEntry(0);
        spr_gr_standalone_1KHz[j] = spr[2];
        spr_gr_err_standalone_1KHz[j] = 0.;
    }

    TGraphErrors *gr1 = new TGraphErrors(25, theta, spr_gr_standalone, theta_err, spr_gr_err_standalone);
    TGraphErrors *gr2 = new TGraphErrors(25, theta, spr_gr_standalone_5_4, theta_err, spr_gr_err_standalone_5_4);
    TGraphErrors *gr3 = new TGraphErrors(25, theta, spr_gr_standalone_mcp, theta_err, spr_gr_err_standalone_mcp);
    TGraphErrors *gr4 = new TGraphErrors(25, theta, spr_gr_standalone_100KHz, theta_err, spr_gr_err_standalone_100KHz);
    TGraphErrors *gr5 = new TGraphErrors(25, theta, spr_gr_standalone_1KHz, theta_err, spr_gr_err_standalone_1KHz);

    gr1->SetTitle("SPR at 6 GeV/c - geometric reco. HRPPD vs 1KHz vs 10 KHz vs 100 KHz dn per square mm vs standard Mcp_Pmt");
    gr1->GetXaxis()->SetTitle("Polar angle (deg)");
    gr1->GetYaxis()->SetTitle("Single Photon Resolution (mrad)");
    gr1->GetYaxis()->SetRangeUser(0, 10);
    gr1->GetXaxis()->SetRangeUser(20, 160);
    gr1->GetXaxis()->SetTitleSize(0.05);
    gr1->GetYaxis()->SetTitleSize(0.05);
    gr1->GetXaxis()->SetTitleOffset(0.8);
    gr1->GetYaxis()->SetTitleOffset(0.8);

    gr1->SetMarkerStyle(kFullCircle);
    gr1->SetMarkerSize(1);
    gr1->SetMarkerColor(1);
    gr1->SetLineColor(1);
    gr1->Draw("APL");

    gr2->SetMarkerStyle(kFullCircle);
    gr2->SetMarkerSize(1);
    gr2->SetMarkerColor(2);
    gr2->SetLineColor(2);
    gr2->Draw("same");

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
